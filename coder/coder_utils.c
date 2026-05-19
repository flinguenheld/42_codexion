/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   coder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 18:16:11 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/19 21:41:18 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

/**
 * @brief Set all coders' status to KILLED.
 */
static void	kill_all_coders(t_coder **coders, t_data *data)
{
	int	index;

	index = 0;
	while (index < data->nb_coders)
	{
		coders[index]->message = KILL;
		index++;
	}
}

char	are_all_coders_over(t_coder **coders, t_data *data, pthread_mutex_t *mutex)
{
	int	index;
	int	done;

	index = 0;
	done = 0;
	pthread_mutex_lock(mutex);
	while (index < data->nb_coders)
	{
		if (coders[index]->coder_data.status == BURNOUT)
		{
			kill_all_coders(coders, data);
				pthread_mutex_unlock(mutex);
			return (1);
		}
		if (coders[index]->coder_data.remain <= 0)
			done++;
		index++;
	}
	if (done == data->nb_coders)
	{
		kill_all_coders(coders, data);
			pthread_mutex_unlock(mutex);
		return (1);
	}
			pthread_mutex_unlock(mutex);
	return (0);
}
