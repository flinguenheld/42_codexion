/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   coder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 18:16:11 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/16 18:16:12 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

/**
 * @brief Loop in all coders to set their status as KILLED.
 */
static void	kill_all_coders(t_coder **coders, t_data *data)
{
	int	index;

	index = 0;
	while (index < data->nb_coders)
	{
		coders[index]->status = KILLED;
		index++;
	}
}

char	are_all_coders_over(t_coder **coders, t_data *data)
{
	int	index;
	int	done;

	index = 0;
	done = 0;
	while (index < data->nb_coders)
	{
		if (coders[index]->status == BURNOUT)
		{
			kill_all_coders(coders, data);
			return (1);
		}
		if (coders[index]->remain <= 0)
			done++;
		index++;
	}
	if (done == data->nb_coders)
	{
		kill_all_coders(coders, data);
		return (1);
	}
	return (0);
}
