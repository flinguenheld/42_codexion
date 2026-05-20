/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:43:34 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/20 15:09:15 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	get_overlapped_index(int index, int nb_elements)
{
	if (index < 0)
		return (nb_elements - 1);
	else if (index >= nb_elements)
		return (0);
	else
		return (index);
}

void	usage(int error)
{
	char	*txt;

	txt = "\n   Orchestrate multiple coders competing for limited USB\n"\
"   dongles using POSIX threads, mutexes, and smart scheduling.\n\n"\
"   Has to be used with these arguments:\n"\
"      - number_of_coders\n"\
"      - time_to_burnout: ms\n"\
"      - time_to_compile: ms\n"\
"      - time_to_debug: ms\n"\
"      - time_to_refactor: ms\n"\
"      - number_of_compiles_required\n"\
"      - dongle_cooldown: ms\n"\
"      - scheduler: fifo or edf\n"\
"\n" \
"examples:\n"\
"./codexion 20 600 50 50 50 20 5 fifo\n"\
"./codexion 4 410 200 100 100 5 10 edf\n";
	if (error)
		fprintf(stderr, "%s", txt);
	else
		printf("%s", txt);
}
