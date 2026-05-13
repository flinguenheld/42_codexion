/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 16:41:18 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/12 16:41:18 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		nb_fail;

	ft_printf("-> %d\n", argc);
	ft_printf("-> %s\n", argv[7]);
	nb_fail = parse(argc, argv, &data);
	if (nb_fail > 0)
	{
		ft_printf_err("%d wrong argument(s).\n", nb_fail);
		usage(1);
	}
	return (0);
}
