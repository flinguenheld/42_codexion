/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 17:55:44 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/13 17:55:44 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../codexion.h"

static int	to_int(int *to, char *value, char *explanation)
{
	int	numeric;

	if (ft_is_integer(value))
	{
		numeric = ft_atoi(value);
		if (numeric >= 1)
		{
			*to = numeric;
			return (0);
		}
	}
	ft_printf_err("%s -> Incorrect value '%s'.\n", explanation, value);
	return (1);
}

char	parse(int argc, char **argv, t_data *data)
{
	char	fail;

	fail = 0;
	if (argc != 9)
		return (9);
	fail += to_int(&data->number_of_coders, argv[1], "Number of coders");
	fail += to_int(&data->time_to_burnout, argv[2], "Time to burnout");
	fail += to_int(&data->time_to_compile, argv[3], "Time to compile");
	fail += to_int(&data->time_to_debug, argv[4], "Time to debug");
	fail += to_int(&data->time_to_refactor, argv[5], "Time to refactor");
	fail += to_int(&data->nb_to_do, argv[6], "Number of compiles required");
	fail += to_int(&data->dongle_cooldown, argv[7], "Dongle cooldown");
	if (ft_strlen(argv[8]) == 4 && ft_strncmp(argv[8], "fifo", 4) == 0)
		data->scheduler = 'f';
	else if (ft_strlen(argv[8]) == 3 && ft_strncmp(argv[8], "edf", 3) == 0)
		data->scheduler = 'e';
	else
	{
		fail += 1;
		ft_printf_err("Scheduler -> Incorrect value '%s'.\n", argv[8]);
	}
	return (fail);
}
