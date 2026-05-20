/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 13:27:03 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/20 15:36:51 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// ----------------------------------------------------------------------------
// ------------------------------------------------------------------- CORE ---

/**
 * @brief Update dongles according to their coder's status.
 *        Then update the buffer to only keep waiting coders.
 *        Filter again buffer to only keep coder with available dongles.
 *        Get one coder according to the scheduler choice (fifo or edf).
 * @return coder's index or -1 if no one is available.
 */
static int	get_next_coder_to_start(t_codexion *codexion, t_data *data)
{
	up_dongles(codexion->dongles,
		codexion->coders,
		data,
		codexion->mutex_coders);
	buffer_get_waiting_coders(codexion->coders,
		codexion->buffer,
		codexion->mutex_coders,
		data->nb_coders);
	buffer_filter_with_dongles(codexion->buffer,
		codexion->dongles,
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
	pthread_mutex_lock(codexion->mutex_coders);
	codexion->coders[index_to_start]->message = START;
	pthread_mutex_unlock(codexion->mutex_coders);
	codexion->dongles[index_to_start] = BUSY;
	codexion->dongles[get_overlapped_index(index_to_start - 1,
			data->nb_coders)] = BUSY;
}

void	run(t_codexion *codexion, t_data *data)
{
	int	index_to_start;
	int	status;

	while (1)
	{
		status = are_all_coders_done(codexion->coders,
				data,
				codexion->mutex_coders);
		if (status > 0)
		{
			if (status == 2)
				kill_all_coders(codexion->coders, data, codexion->mutex_coders);
			break ;
		}
		index_to_start = get_next_coder_to_start(codexion, data);
		if (index_to_start >= 0)
		{
			start_coder(codexion, data, index_to_start);
		}
		usleep(10);
	}
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------- OPEN / CLOSE ---

t_codexion	init_codexion(t_data *data)
{
	t_codexion	codexion;
	t_coder		*new_one;
	int			index;

	codexion.coders = malloc(data->nb_coders * sizeof(t_coder *));
	codexion.buffer = malloc(data->nb_coders * sizeof(t_coder *));
	codexion.dongles = init_dongles(data);
	codexion.mutex_coders = malloc(sizeof(pthread_mutex_t));
	codexion.mutex_stdout = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(codexion.mutex_coders, NULL);
	pthread_mutex_init(codexion.mutex_stdout, NULL);
	index = 0;
	while (index < data->nb_coders)
	{
		new_one = new_coder(data,
				codexion.mutex_coders,
				codexion.mutex_stdout,
				index + 1);
		pthread_create(&new_one->thread, NULL, coder_thread, (void *)new_one);
		codexion.coders[index] = new_one;
		index++;
	}
	return (codexion);
}

void	close_codexion(t_data *data, t_codexion codexion)
{
	while (data->nb_coders > 0)
	{
		pthread_join(codexion.coders[data->nb_coders - 1]->thread, NULL);
		free(codexion.coders[data->nb_coders - 1]);
		data->nb_coders--;
	}
	pthread_mutex_destroy(codexion.mutex_coders);
	pthread_mutex_destroy(codexion.mutex_stdout);
	free(codexion.mutex_coders);
	free(codexion.mutex_stdout);
	free(codexion.coders);
	free(codexion.buffer);
	free(codexion.dongles);
}
