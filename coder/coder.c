/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:45:30 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/22 01:13:53 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

/**
 * @brief Read the message field in t_coder (using the mutex)
 *        to update the coder_data status if needed.
 *
 *        This function allows the main thread to start / kill coders.
 */
static void	read_message(t_coder *coder, t_coder_data *coder_data)
{
	pthread_mutex_lock(coder->mutexes.message);
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
	pthread_mutex_unlock(coder->mutexes.message);
}

/**
 * @brief Create a copy of coder_data (using the mutex).
 *        Thanks to the copy, the coder only uses the copy and
 *        doesn't need to lock a mutex all the time.
 */
static t_coder_data	clone_coder_data(t_coder *coder)
{
	t_coder_data	cloned_data;

	pthread_mutex_lock(coder->mutexes.coders);
	cloned_data = coder->coder_data;
	pthread_mutex_unlock(coder->mutexes.coders);
	return (cloned_data);
}

/**
 * @brief Clone the coder_data copy into the coder (using the mutex).
 */
static void	merge_coder_data(t_coder_data coder_data, t_coder *coder)
{
	pthread_mutex_lock(coder->mutexes.coders);
	coder->coder_data = coder_data;
	pthread_mutex_unlock(coder->mutexes.coders);
}

void	*coder_thread(void *c)
{
	t_coder			*coder;
	t_coder_data	previous;
	t_coder_data	coder_data;

	coder = (t_coder *)c;
	previous = clone_coder_data(coder);
	coder_data = previous;
	while (1)
	{
		read_message(coder, &coder_data);
		coder_process_run(&coder_data, coder);
		if (memcmp(&previous, &coder_data, sizeof(t_coder_data)) != 0)
		{
			merge_coder_data(coder_data, coder);
			previous = coder_data;
		}
		if (coder_data.status == DONE && coder->timestamp_release_dongles <= 0)
			break ;
		if (coder_data.status == BURNOUT || coder_data.status == KILLED)
			break ;
		usleep(2);
	}
	return (NULL);
}
