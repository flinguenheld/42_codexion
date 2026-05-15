/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:45:30 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/15 17:43:32 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

t_coder	*new_coder(t_data *data, pthread_mutex_t *mutex)
{
	t_coder		*new_coder;

	new_coder = malloc(sizeof(t_coder));
	new_coder->status = WAITING;
	new_coder->remain = data->nb_to_do;
	new_coder->data = data;
	new_coder->mutex = mutex;
	return (new_coder);
}

void	*coder_process(void *c)
{
	t_coder	*coder;
	long	time_ms;

	usleep(2*100000);

	coder = (t_coder *)c;
	// Block the mutex

	// Loop as long as Active

	// Up status
	time_ms = get_time() - coder->data->timestamp_start;
    pthread_mutex_lock(coder->mutex);
    printf("time ms: %lu\n", time_ms);

    printf("%lu mutex in thread: %p\n", time_ms , coder->mutex);
    pthread_mutex_unlock(coder->mutex);

	// Print '1 1 is compiling'
	// Still active ?? (is it enough or more rigorous ?)

	// Up status
	// Print '201 1 is debugging'
	// Still active ??

	// Up status
	// Print '401 1 is refactoring'
	// Still active ??

	// Up status
	// Not print 'cool down'
	// Still active ??

	// Up status
	// Free the mutex

	return NULL;
}
