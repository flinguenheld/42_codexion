/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 13:27:03 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/20 00:09:51 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "coder/coder.h"
#include <stdio.h>

t_codexion	init_codexion(t_data *data)
{
	t_codexion	codexion;
	t_coder		*new_one;
	int			index;

	codexion.coders = malloc(data->nb_coders * sizeof(t_coder *));
	codexion.buffer = malloc(data->nb_coders * sizeof(t_coder *));
	codexion.dongles = init_dongles(data);
	codexion.mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(codexion.mutex, NULL);
	index = 0;
	while (index < data->nb_coders)
	{
		new_one = new_coder(data, codexion.mutex, index + 1);
		pthread_create(&new_one->thread, NULL, coder_process, (void *)new_one);
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
	pthread_mutex_destroy(codexion.mutex);
	free(codexion.mutex);
	free(codexion.coders);
	free(codexion.buffer);
	free(codexion.dongles);
}

void	run(t_codexion *codexion, t_data *data)
{
	int	index_to_start;

	while (!are_all_coders_over(codexion->coders, data, codexion->mutex))
	{
		index_to_start = -1;
		up_dongles(codexion->dongles, codexion->coders, data);
		buffer_get_waiting_coders(codexion->coders, codexion->buffer,
								codexion->mutex, data->nb_coders);
		buffer_filter(codexion->buffer, codexion->dongles, data->nb_coders);
		if (data->scheduler == 'e')
			index_to_start = edf(codexion->buffer, data->nb_coders);
		else
			index_to_start = fifo(codexion->buffer, data->nb_coders);

		// printf("RUN -> TO START: %d\n", index_to_start);
			
		if (index_to_start >= 0)
		{
			pthread_mutex_lock(codexion->mutex);
			codexion->coders[index_to_start]->message = START;
			pthread_mutex_unlock(codexion->mutex);
			codexion->dongles[index_to_start] = BUSY;
			codexion->dongles[get_overlapped_index(index_to_start - 1,
					data->nb_coders)] = BUSY;
		}
		usleep(10);
	}
}
