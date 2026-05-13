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

void	simulate_process(int time_ms)
{

	usleep(time_ms * 1000);
}

void	coder_process(void *d)
{
	t_data	*data;
	int		time;

	data = (t_data *)d;
	// Block the mutex

	// Loop as long as Active

		// Up status
		usleep(data->time_to_compile * 1000);
		// Print '1 1 is compiling'
		// Still active ?? (is it enough or more rigorous ?)

		// Up status
		// Print '201 1 is debugging'
		// Still active ??

		// Up status
		// Print '401 1 is refactoring'
		// Still active ??

		// Up status
		// Not print 'cool down'
		// Still active ??

		// Up status
	// Free the mutex
}

void	printer_manager(void *blah)
{

}

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

	// Create an array of n threads

	// Create an array of n dongles

	// Create the manager

	return (0);
}
