/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 17:55:44 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/18 18:12:30 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	to_int(int *to, char *value, char *explanation)
{
	int	numeric;

	numeric = atoi(value);
	if (numeric >= 1)
	{
		*to = numeric;
		return (0);
	}
	fprintf(stderr, "%s -> Incorrect value '%s'.\n", explanation, value);
	return (1);
}

char	parse(int argc, char **argv, t_data *data)
{
	char	fail;

	fail = 0;
	if (argc != 9)
		return (9);
	fail += to_int(&data->nb_coders, argv[1], "Number of coders");
	fail += to_int(&data->time_burnout, argv[2], "Time to burnout");
	fail += to_int(&data->time_compile, argv[3], "Time to compile");
	fail += to_int(&data->time_debug, argv[4], "Time to debug");
	fail += to_int(&data->time_refact, argv[5], "Time to refactor");
	fail += to_int(&data->nb_to_do, argv[6], "Number of compiles required");
	fail += to_int(&data->time_cooldown, argv[7], "Dongle cooldown");
	if (strlen(argv[8]) == 4 && strcmp(argv[8], "fifo") == 0)
		data->scheduler = 'f';
	else if (strlen(argv[8]) == 3 && strcmp(argv[8], "edf") == 0)
		data->scheduler = 'e';
	else
	{
		fail += 1;
		fprintf(stderr, "Scheduler -> Incorrect value '%s'.\n", argv[8]);
	}
	data->timestamp_start = get_time();
	return (fail);
}
