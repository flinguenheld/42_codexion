/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 16:41:18 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/15 23:11:36 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include "dongle/dongle.h"

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
