/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 10:19:48 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/18 10:44:51 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scheduler.h"

void	buffer_get_waiting_cd(t_coder **coders, t_coder **buffer, int nb_coders)
{
	int		index;

	index = 0;
	while (index < nb_coders)
	{
		if (coders[index]->status == WAITING)
			buffer[index] = coders[index];
		else
			buffer[index] = NULL;
		index++;
	}
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
				buffer[index] = NULL;
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
			if (found < 0 || buffer[index]->timestamp_last_comp
				< buffer[found]->timestamp_last_comp)
				found = index;
		}
		index++;
	}
	return (found);
}
