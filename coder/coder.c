/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:45:30 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/15 23:18:03 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

/**
 * @brief Create and init a new coder.
 * @return A coder pointer to free
 */
t_coder	*new_coder(t_data *data, pthread_mutex_t *mutex, int id)
{
	t_coder		*new_coder;

	new_coder = malloc(sizeof(t_coder));
	new_coder->timestamp_start = get_time();
	new_coder->timestamp_last_compilation = get_time();
	new_coder->remain = data->nb_to_do;
	new_coder->status = START; // TODO: TO UP WITH THE MANAGER
	new_coder->mutex = mutex;
	new_coder->data = data;
	new_coder->id = id;
	return (new_coder);
}

/**
 * @brief Print the formated status, do not manage the mutex.
 */
static void	print_status(t_coder *coder)
{
	int	time;

	time = get_time() - coder->data->timestamp_start;
	if (coder->status == COMPILING)
	{
		printf("%5d %3d has taken a dongle\n", time, coder->id);
		printf("%5d %3d has taken a dongle\n", time, coder->id);
		printf("%5d %3d is compiling\n", time, coder->id);
	}
	else if (coder->status == DEBUGGING)
		printf("%5d %3d is debugging\n", time, coder->id);
	else if (coder->status == REFACTORING)
		printf("%5d %3d is refactoring\n", time, coder->id);
	else if (coder->status == BURNOUT)
		printf("%5d %3d has burned out\n", time, coder->id);
}

/**
 * @brief Active the mutex to update the status, the timestamp and print.
 */
static void	up_status(t_coder *coder, enum e_coder_status new_status)
{
	pthread_mutex_lock(coder->mutex);
	coder->status = new_status;
	coder->timestamp_start = get_time();
	if (new_status == COMPILING)
		coder->timestamp_last_compilation = get_time();
	print_status(coder);
	pthread_mutex_unlock(coder->mutex);
}

static void	proceed(t_coder *coder)
{
	int	elapsed;

	elapsed = get_time() - (long)coder->timestamp_start;
	if (coder->status == START)
		up_status(coder, COMPILING);
	else if (coder->status == COMPILING && elapsed > coder->data->time_compile)
		up_status(coder, DEBUGGING);
	else if (coder->status == DEBUGGING && elapsed > coder->data->time_debug)
		up_status(coder, REFACTORING);
	else if (coder->status == REFACTORING && elapsed > coder->data->time_refact)
	{
		// Also release the dongles here ?
		// up_status(coder, WAITING);
		up_status(coder, KILLED);
	}
}

void	*coder_process(void *c)
{
	t_coder	*coder;

	coder = (t_coder *)c;
	while (coder->status != KILLED && coder->status != BURNOUT)
	{
		proceed(coder);
		usleep(500);
	}
	return NULL;
}
