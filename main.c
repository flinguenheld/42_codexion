/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 16:41:18 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/15 15:55:31 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


int	main(int argc, char **argv)
{
	t_data	data;
	int		nb_fail;
	t_codexion	codexion;

	printf("-> %d\n", argc);
	printf("-> %s\n", argv[7]);
	nb_fail = parse(argc, argv, &data);
	if (nb_fail > 0)
	{
		fprintf( stderr,"%d wrong argument(s).\n", nb_fail);
		usage(1);
		return (1);
	}

	codexion = init_codexion(data);
	printf("hello\n");
	printf("hello\n");
	printf("hello\n");
	printf("hello\n");

	
	// printf("MAIN \n\n");
	// printf("ID coder at 0 %lu\n", codexion.coders[0]->thread);
	// printf("ID coder at 1 %lu\n", codexion.coders[1]->thread);
	// printf("ID coder at 2 %lu\n", codexion.coders[2]->thread);
	// printf("\n\n");


	// Create the manager
	// usleep(5 * 100000);

	close_codexion(data, codexion);

	return (0);
}
