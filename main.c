/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 16:41:18 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/20 15:09:14 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser/parser.h"
#include "codex/codexion.h"

int	main(int argc, char **argv)
{
	t_data		data;
	int			nb_fail;
	t_codexion	codexion;

	nb_fail = parse(argc, argv, &data);
	if (nb_fail > 0)
	{
		fprintf(stderr, "%d wrong argument(s).\n", nb_fail);
		usage(1);
		return (1);
	}
	codexion = init_codexion(&data);
	run(&codexion, &data);
	close_codexion(&data, codexion);
	return (0);
}
