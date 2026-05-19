/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:45:30 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/18 18:12:30 by flinguen         ###   ########.fr       */
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
	new_coder->mutex = mutex;
	new_coder->data = data;
	new_coder->message = 0;
	new_coder->id = id;
	new_coder->coder_data = (t_coder_data){
										.status = WAITING,
										.timestamp_last_comp = -1,
										.timestamp = get_time(),
										.remain = data->nb_to_do
									};
	return (new_coder);
}

/**
 * @brief Print the formated status, do not manage the mutex.
 */
static void	print_status(t_coder_data *coder_data, t_coder *coder)
{
	int	time;

	pthread_mutex_lock(coder->mutex);
	time = get_time() - coder->data->timestamp_start;
	if (coder_data->status == COMPILING)
	{
		printf("%6d    C%-3d  has taken a dongle\n", time, coder->id);
		printf("%6d    C%-3d  has taken a dongle\n", time, coder->id);
		printf("%6d    C%-3d  is compiling (%d remain) 🤖\n", time, coder->id,
			coder_data->remain - 1);
	}
	else if (coder_data->status == DEBUGGING)
		printf("%6d    C%-3d  is debugging 🪲\n", time, coder->id);
	else if (coder_data->status == REFACTORING)
		printf("%6d    C%-3d  is refactoring 🧼\n", time, coder->id);
	else if (coder_data->status == BURNOUT)
		printf("%6d    C%-3d  🔥 has burned out 🔥\n", time, coder->id);
	pthread_mutex_unlock(coder->mutex);
}

/**
 * @brief Active the mutex to update the status, the timestamp and print.
 */
static void	up_status(t_coder_data *coder_data, enum e_coder_status new_status, t_coder *coder)
{
	coder_data->status = new_status;
	coder_data->timestamp = get_time();
	if (new_status == COMPILING)
		coder_data->timestamp_last_comp = get_time();
	else if (new_status == WAITING)
	{
		coder_data->timestamp = get_time();
		coder_data->remain--;
		if (coder_data->remain <= 0)
			coder_data->status = DONE;
	}
	print_status(coder_data, coder);
}

// static void	proceed(t_coder *coder)
static void	proceed(t_coder_data *coder_data, t_coder *coder)
{
	int	elapsed;

	elapsed = get_time() - coder_data->timestamp;
	if (coder_data->status == STARTING)
		up_status(coder_data, COMPILING, coder);
	else if (coder_data->status == COMPILING && elapsed > coder->data->time_compile)
		up_status(coder_data, DEBUGGING, coder);
	else if (coder_data->status == DEBUGGING && elapsed > coder->data->time_debug)
		up_status(coder_data, REFACTORING, coder);
	else if (coder_data->status == REFACTORING && elapsed > coder->data->time_refact)
		up_status(coder_data, WAITING, coder);
	else if (coder_data->status == WAITING && elapsed > coder->data->time_burnout)
		up_status(coder_data, BURNOUT, coder);
}

static void	has_message(t_coder *coder, t_coder_data *coder_data)
{
	pthread_mutex_lock(coder->mutex);
	if (coder->message == KILL)
	{
		coder->message = NONE;
		coder_data->status = KILLED;
	}
	else if (coder->message == START && coder_data->status == WAITING)
	{
		coder->message = NONE;
		coder_data->status = STARTING;
	}
	pthread_mutex_unlock(coder->mutex);
}

void	*coder_process(void *c)
{
	t_coder			*coder;
	t_coder_data	previous;
	t_coder_data	coder_data;

	coder = (t_coder *)c;
	previous = clone_coder_data(coder);
	coder_data = previous;
	while (1)
	{
		has_message(coder, &coder_data);

		// TODO: Manage the KILL status
		proceed(&coder_data, coder);
		if (memcmp(&previous, &coder_data, sizeof(t_coder_data)) != 0)
		{
			merge_coder_data(coder_data, coder);
			if (coder_data.remain == 0)
				break;
			if (coder_data.status == BURNOUT || coder_data.status == KILLED)
				break;
			previous = coder_data;
		}
		usleep(800);
	}
	return (NULL);
}

t_coder_data	clone_coder_data(t_coder *coder)
{
	t_coder_data	cloned_data;

	pthread_mutex_lock(coder->mutex);
	cloned_data = coder->coder_data;
	pthread_mutex_unlock(coder->mutex);
	return cloned_data;
}

void	merge_coder_data(t_coder_data coder_data, t_coder *coder)
{
	pthread_mutex_lock(coder->mutex);
	coder->coder_data = coder_data;
	pthread_mutex_unlock(coder->mutex);
}
