/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 16:41:18 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/18 10:44:51 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "coder/coder.h"
#include "dongle/dongle.h"
#include "scheduler/scheduler.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		nb_fail;
	t_codexion	codexion;

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
		buffer_get_waiting_cd(codexion.coders, codexion.buffer, data.nb_coders);
		buffer_filter(codexion.buffer, codexion.dongles, data.nb_coders);
		int to_start = fifo(codexion.buffer, data.nb_coders);
		if (to_start >= 0)
		{
			pthread_mutex_lock(codexion.mutex);
			codexion.coders[to_start]->status = START;
			pthread_mutex_unlock(codexion.mutex);
			codexion.dongles[to_start] = BUSY;
			codexion.dongles[get_overlapped_index(to_start - 1, data.nb_coders)] = BUSY;
		}
		usleep(10);
	}

	printf("Done ! \n");
	close_codexion(&data, codexion);
	return (0);
}
