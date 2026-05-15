/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 13:27:03 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/14 13:27:03 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_codexion	init_codexion(t_data data)
{
	t_codexion	codexion;
	int			index;
	t_coder		*new_one;

	codexion.coders = malloc(data.number_of_coders * sizeof(t_coder *));
	codexion.mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(codexion.mutex, NULL);

	index = 0;
	while (index < data.number_of_coders)
	{
		// Create dongles

		// Affect them into coders
		new_one = new_coder(&data, codexion.mutex);
	    pthread_create(&new_one->thread, NULL, coder_process, (void *)new_one);

		codexion.coders[index] = new_one;
		index++;
	}
	return codexion;
}

void	close_codexion(t_data data, t_codexion codexion)
{
	// Loop in threads and wait them ?

	// Or set them has over ?

	while (data.number_of_coders > 0)
	{
			pthread_join(codexion.coders[data.number_of_coders - 1]->thread, NULL);
		free(codexion.coders[data.number_of_coders - 1]);
		data.number_of_coders--;
	}
	pthread_mutex_destroy(codexion.mutex);
	free(codexion.mutex);
	free(codexion.coders);
}
