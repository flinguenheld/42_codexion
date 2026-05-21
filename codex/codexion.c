/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 13:27:03 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/21 22:37:27 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

/**
 * @brief Update buffers to only keep waiting coders.
 *        Filter again to only keep coders with available dongles.
 *        Then get one coder according to the scheduler choice (fifo or edf).
 * @return coder's index or -1 if no one is available.
 */
static int	get_next_coder_to_start(t_codexion *codexion, t_data *data)
{
	buffer_get_waiting_coders(codexion->coders,
		codexion->buffer,
		codexion->mutexes.coders,
		data->nb_coders);
	buffer_filter_with_dongles(codexion->buffer,
		codexion->dongles,
		codexion->mutexes.dongles,
		data->nb_coders);
	if (data->scheduler == 'e')
		return (edf(codexion->buffer, data->nb_coders));
	else
		return (fifo(codexion->buffer, data->nb_coders));
}

/**
 * @brief Send a message to the coder to start (using mutex)
 *        Update the associated dongle to BUSY
 *
 *        (no check on index_to_start)
 */
static void	start_coder(t_codexion *codexion, t_data *data, int index_to_start)
{
	pthread_mutex_lock(codexion->mutexes.coders);
	codexion->coders[index_to_start]->message = START;
	pthread_mutex_unlock(codexion->mutexes.coders);
	codexion->dongles[index_to_start]++;
	codexion->dongles[get_overlapped_index(index_to_start - 1,
			data->nb_coders)]++;
}

void	run(t_codexion *codexion, t_data *data)
{
	int	index_to_start;
	int	status;

	while (1)
	{
		status = are_all_coders_done(codexion->coders,
				data,
				codexion->mutexes.coders);
		if (status > 0)
		{
			if (status == 2)
				kill_all_coders(codexion->coders,
					data, codexion->mutexes.coders);
			break ;
		}
		index_to_start = get_next_coder_to_start(codexion, data);
		if (index_to_start >= 0)
		{
			start_coder(codexion, data, index_to_start);
		}
		usleep(2);
	}
}
