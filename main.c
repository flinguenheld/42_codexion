/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 16:41:18 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/17 23:49:58 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "coder/coder.h"
#include "dongle/dongle.h"
#include <stdio.h>

void get_waiting_coders(t_coder **coders, t_coder **buffer, int nb_coders)
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

void filter_available_dongles(t_coder **buffer, enum e_dongle_status *dongles,
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
				// printf("these can't: %d %d\n", index_prev, index);
				buffer[index] = NULL;
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
			if (found < 0 || buffer[index]->timestamp_last_comp < buffer[found]->timestamp_last_comp)
			{
				// printf("found this one: %d\n", index);
				found = index;
			}
		}
		index++;
	}
	return (found);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		nb_fail;
	t_codexion	codexion;

	// printf("-> %d\n", argc);
	// printf("-> %s\n", argv[7]);
	nb_fail = parse(argc, argv, &data);
	if (nb_fail > 0)
	{
		fprintf( stderr,"%d wrong argument(s).\n", nb_fail);
		usage(1);
		return (1);
	}

	codexion = init_codexion(&data);


	while (!are_all_coders_over(codexion.coders, &data))
	{
		up_dongles(codexion.dongles, codexion.coders, &data);
		// printf("remain first coder: %d\n", codexion.coders[0]->remain);
		// printf("remain first coder: %d\n", codexion.coders[1]->remain);
		// printf("remain first coder: %d\n", codexion.coders[2]->remain);
		get_waiting_coders(codexion.coders, codexion.buffer, data.nb_coders);
		filter_available_dongles(codexion.buffer, codexion.dongles,
							data.nb_coders);

		// FIFO -> Get the first arrived

		int blah = fifo(codexion.buffer, data.nb_coders);

		if (blah >= 0)
		{
			pthread_mutex_lock(codexion.mutex);
			// printf("start this one: %d\n", blah);
			codexion.coders[blah]->status = START;
			pthread_mutex_unlock(codexion.mutex);
			codexion.dongles[blah] = BUSY;
			codexion.dongles[get_overlapped_index(blah - 1, data.nb_coders)] = BUSY;
		}
		usleep(10);
	}

	printf("Done ! \n");

	// printf("MAIN \n\n");
	// printf("ID coder at 0 %lu\n", codexion.coders[0]->thread);
	// printf("ID coder at 1 %lu\n", codexion.coders[1]->thread);
	// printf("ID coder at 2 %lu\n", codexion.coders[2]->thread);
	// printf("\n\n");

	// Create the manager
	// usleep(5 * 100000);

	close_codexion(&data, codexion);

	return (0);
}
