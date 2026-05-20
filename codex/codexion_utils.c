/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   codexion_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:06:46 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/20 15:09:14 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

char	are_all_coders_done(t_coder **coders,
							t_data *data,
							pthread_mutex_t *mutex)
{
	int		index;
	int		done;
	char	result;

	result = 0;
	index = 0;
	done = 0;
	pthread_mutex_lock(mutex);
	while (index < data->nb_coders)
	{
		if (coders[index]->coder_data.status == BURNOUT)
		{
			result = 2;
			break ;
		}
		if (coders[index]->coder_data.remain <= 0)
			done++;
		index++;
	}
	pthread_mutex_unlock(mutex);
	if (done == data->nb_coders)
		result = 1;
	return (result);
}

void	kill_all_coders(t_coder **coders, t_data *data, pthread_mutex_t *mutex)
{
	int	index;

	index = 0;
	pthread_mutex_lock(mutex);
	while (index < data->nb_coders)
	{
		coders[index]->message = KILL;
		index++;
	}
	pthread_mutex_unlock(mutex);
}
