/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:45:30 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/18 18:12:30 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include "../utils/utils.h"
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
	DONE, // USEFULL ???
};

enum e_coder_message
{
	START,
	KILL,
	NONE,
};

typedef struct s_coder_data
{
	enum e_coder_status	status;
	int		remain;
	long	timestamp;
	long	timestamp_last_comp;
} t_coder_data;

typedef struct s_coder
{
	int					id;
	enum e_coder_message		message;
	pthread_t			thread;
	t_data				*data;
	pthread_mutex_t		*mutex;
	t_coder_data		coder_data;
}	t_coder;

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

/**
 * @brief
 */
t_coder	*new_coder(t_data *data, pthread_mutex_t *mutex, int id);

/**
 * @brief
 */
void	*coder_process(void *c);

/**
 * @brief Loop in coders to check their status and their remaining.
 *        Kill all coders if one of them has burned out.
 * @return 1 if one has burned out or all coders have finished their work.
 */
// char	are_all_coders_over(t_coder **coders, t_data *data);
char	are_all_coders_over(t_coder **coders, t_data *data, pthread_mutex_t *mutex);

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

/**
 * @brief
 */
t_coder_data	clone_coder_data(t_coder *coder);

/**
 * @brief
 */
void			merge_coder_data(t_coder_data coder_data, t_coder *coder);

#endif
