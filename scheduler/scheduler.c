/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 10:19:48 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/20 00:09:51 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scheduler.h"
#include <stdio.h>

void	buffer_get_waiting_coders(t_coder **coders, t_coder **buffer,
							pthread_mutex_t *mutex, int nb_coders)
{
	int		index;

	index = 0;
	// TODO: Add mutex -------------------------------------------------------------
	// TODO: Add mutex -------------------------------------------------------------
	// TODO: Add mutex -------------------------------------------------------------
	// TODO: Add mutex -------------------------------------------------------------

	pthread_mutex_lock(mutex);
	while (index < nb_coders)
	{
		if (coders[index]->coder_data.status == WAITING)
		{
			// printf("this one is waiting: %d\n", index+1);
			buffer[index] = coders[index];
			
		}
		else
		{
			// printf("this one is NOT waiting: %d\n", index+1);
			buffer[index] = NULL;
			
		}
		index++;
	}
	pthread_mutex_unlock(mutex);
}

void	buffer_filter(t_coder **buffer,
				enum e_dongle_status *dongles,
				int nb_coders)
{
	int		index;
	int		index_prev;

	index = 0;
	while (index < nb_coders)
	{
		if (buffer[index])
		{
			index_prev = get_overlapped_index(index - 1, nb_coders);
			if (dongles[index_prev] == BUSY || dongles[index] == BUSY)
			{
				// printf("this one is has a dongle busy: %d\n", index+1);
				buffer[index] = NULL;
			}
			else{
				// printf("this one has two dongles OK: %d\n", index+1);
				
			}
		}
		index++;
	}
}

int	fifo(t_coder **buffer, int nb_coders)
{
	int	index;
	int	found;

	index = 0;
	found = -1;
	while (index < nb_coders)
	{
		if (buffer[index])
		{
			if (found < 0 || buffer[index]->coder_data.timestamp_last_comp
				< buffer[found]->coder_data.timestamp_last_comp)
				found = index;
		}
		index++;
	}
	return (found);
}

int	edf(t_coder **buffer, int nb_coders)
{
	int	index;
	int	found;

	index = nb_coders - 1;
	found = -1;
	while (index >= 0)
	{
		if (buffer[index])
		{
			if (found < 0 || (buffer[index]->coder_data.timestamp_last_comp
				< buffer[found]->coder_data.timestamp_last_comp))
				found = index;
		}
		index--;
	}
	return (found);
}
