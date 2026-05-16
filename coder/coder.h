/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:45:30 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/15 23:11:36 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include "../data/data.h"
# include "../utils/utils.h"
# include "sys/time.h"
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

enum e_coder_status
{
	REFACTORING,
	COMPILING,
	DEBUGGING,
	WAITING,
	BURNOUT,
	KILLED,
	START,
};

typedef struct s_coder
{
	enum e_coder_status	status;
	int					id;
	int					remain;
	long				timestamp_start;
	long				timestamp_last_compilation;
	pthread_t			thread;
	t_data				*data;
	pthread_mutex_t		*mutex;
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

#endif
