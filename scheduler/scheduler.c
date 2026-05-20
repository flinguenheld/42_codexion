/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 10:19:48 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/20 15:09:14 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scheduler.h"

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------- BUFFER ---

void	buffer_get_waiting_coders(t_coder **coders,
			t_coder **buffer,
			pthread_mutex_t *mutex,
			int nb_coders)
{
	int		index;

	index = 0;
	pthread_mutex_lock(mutex);
	while (index < nb_coders)
	{
		if (coders[index]->coder_data.status == WAITING)
			buffer[index] = coders[index];
		else
			buffer[index] = NULL;
		index++;
	}
	pthread_mutex_unlock(mutex);
}

void	buffer_filter_with_dongles(t_coder **buffer,
				enum e_dongle_status *dongles,
				int nb_coders)
{
	int		index;
	int		index_previous;

	index = 0;
	while (index < nb_coders)
	{
		if (buffer[index])
		{
			index_previous = get_overlapped_index(index - 1, nb_coders);
			if (dongles[index_previous] == BUSY || dongles[index] == BUSY)
				buffer[index] = NULL;
		}
		index++;
	}
}

// ----------------------------------------------------------------------------
// ------------------------------------------------------------- FIFO / EDF ---

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
