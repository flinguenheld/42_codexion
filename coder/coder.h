/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:45:30 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/21 21:41:56 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include "../utils/utils.h"
# include "../mutex/mutex.h"
# include "../data/data.h"
# include "sys/time.h"
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>

enum e_coder_status
{
	REFACTORING,
	COMPILING,
	DEBUGGING,
	STARTING,
	WAITING,
	BURNOUT,
	KILLED,
};

enum e_coder_message
{
	NONE,
	START,
	KILL,
};

typedef struct s_coder_data
{
	enum e_coder_status	status;
	int					remain;
	long				timestamp;
	long				timestamp_last_comp;
}	t_coder_data;

typedef struct s_coder_dongles
{
	char			*left;
	char			*right;
	pthread_mutex_t	*mutex;
}	t_coder_dongles;

typedef struct s_coder
{
	int						id;
	enum e_coder_message	message;
	t_coder_dongles			dongles;
	pthread_t				thread;
	t_data					*data;
	t_coder_data			coder_data;
	t_mutexes				mutexes;
}	t_coder;

// ----------------------------------------------------------------------------
// ---------------------------------------------------------------- PROCESS ---
// Perform the Compilation / Debugging / Refactoring simulations
// They are just waiting times
// Once launched, thoses functions allow the coder to change its state
// according to the subject rules and the data times.
// Print in stdout when its state changes.
// From STARTING to WAITING up to DONE

/**
 * @brief Print the formated status with the print mutex.
 */
void	coder_process_print_status(t_coder_data *coder_data, t_coder *coder);

/**
 * @brief Up the coder data with the new status and call
 *        the print process function.
 */
void	coder_process_up_status(t_coder_data *coder_data,
			enum e_coder_status new_status,
			t_coder *coder);

/**
 * @brief Simulate the process by checking the current status and the time.
 *        If needed, call the coder_process_up_status function.
 */
void	coder_process_run(t_coder_data *coder_data, t_coder *coder);

/**
 * @brief Coder core function
 *        Loops until the coder has been killed, burned out or finished all
 *        of its compilations.
 *
 *        Clone the coder_data to minimise mutex use and merge them
 *        to the coder when necessary (status change).
 *
 *        The main thread can send a 'message' to the thread to
 *        start or kill it.
 *        The message is stored in the t_coder as e_coder_message.
 */
void	*coder_thread(void *c);

// ----------------------------------------------------------------------------
// ------------------------------------------------------------------## NEW ---

/**
 * @brief Create and init a new coder.
 * @return A coder pointer to free
 */
t_coder	*new_coder(t_data *data,
		t_mutexes mutexes,
		int id);

/**
 * @brief Init the dongles and the mutex in coder.
 */
void	coder_attach_dongles(t_coder *coder,
		char	*dongle_left,
		char	*dongle_right,
		pthread_mutex_t *mutex);

#endif
