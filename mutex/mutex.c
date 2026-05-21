/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 17:00:52 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/21 17:00:52 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutex.h"

t_mutexes	init_mutexes(void)
{
	t_mutexes mutexes;

	mutexes.coders = malloc(sizeof(pthread_mutex_t));
	mutexes.stdout = malloc(sizeof(pthread_mutex_t));
	mutexes.message = malloc(sizeof(pthread_mutex_t));
	mutexes.dongles = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mutexes.coders, NULL);
	pthread_mutex_init(mutexes.stdout, NULL);
	pthread_mutex_init(mutexes.message, NULL);
	pthread_mutex_init(mutexes.dongles, NULL);
	return mutexes;
}

void	close_mutexes(t_mutexes *mutexes)
{
	pthread_mutex_destroy(mutexes->coders);
	pthread_mutex_destroy(mutexes->stdout);
	pthread_mutex_destroy(mutexes->message);
	pthread_mutex_destroy(mutexes->dongles);
	free(mutexes->coders);
	free(mutexes->stdout);
	free(mutexes->message);
	free(mutexes->dongles);
}
