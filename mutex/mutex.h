/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   mutex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 17:00:52 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/21 17:00:52 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEX_H
# define MUTEX_H

# include <stdlib.h>
# include <pthread.h>

typedef struct s_mutexes
{
	pthread_mutex_t	*coders;
	pthread_mutex_t	*stdout;
	pthread_mutex_t	*message;
	pthread_mutex_t	*dongles;
}	t_mutexes;

/**
 * @brief Create a struct t_mutexes and fill it.
 *        Malloc and init all fields.
 *
 *        Use the 'close_mutexes' function to free everything.
 */
t_mutexes	init_mutexes(void);

/**
 * @brief Cleanly close mutexes.
 *        Free all pointers openned by 'init_mutexes'.
 */
void		close_mutexes(t_mutexes *mutexes);

#endif
