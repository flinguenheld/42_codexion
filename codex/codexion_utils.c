/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   codexion_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 12:06:46 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/21 22:37:27 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

char	are_all_coders_done(t_coder **coders,
							t_data *data,
							pthread_mutex_t *mutex)
{
	int		index;
	char	result;

	result = 1;
	index = 0;
	pthread_mutex_lock(mutex);
	while (index < data->nb_coders)
	{
		if (coders[index]->coder_data.status == BURNOUT)
		{
			result = 2;
			break ;
		}
		if (coders[index]->coder_data.remain > 0)
			result = 0;
		index++;
	}
	pthread_mutex_unlock(mutex);
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

// ----------------------------------------------------------------------------
// ----------------------------------------------------------- INIT / CLOSE ---

/**
 * @brief Init a coder_dongles which will allow the coder to set its coders
 *        as busy.
 */
static t_coder_dongles	connect_dongles(t_codexion *codex,
			int index,
			int nb_coders)
{
	t_coder_dongles	dongles;

	dongles.left = &codex->dongles[get_overlapped_index(index - 1, nb_coders)];
	dongles.right = &codex->dongles[index];
	dongles.mutex = codex->mutexes.dongles;
	return (dongles);
}

t_codexion	init_codexion(t_data *data)
{
	t_codexion	codexion;
	t_coder		*new_one;
	int			index;

	codexion.coders = malloc(data->nb_coders * sizeof(t_coder *));
	codexion.buffer = malloc(data->nb_coders * sizeof(t_coder *));
	codexion.mutexes = init_mutexes();
	codexion.dongles = init_dongles(data);
	index = 0;
	while (index < data->nb_coders)
	{
		new_one = new_coder(data, codexion.mutexes, index + 1);
		new_one->dongles = connect_dongles(&codexion, index, data->nb_coders);
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
	close_mutexes(&codexion.mutexes);
	free(codexion.coders);
	free(codexion.buffer);
	free(codexion.dongles);
}
