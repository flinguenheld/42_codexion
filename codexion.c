/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 13:27:03 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/14 13:27:03 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void* foo(void* arg) {
    
    // Get current thread ID
    pthread_t thisThread = pthread_self();
    printf("Current thread ID: %lu\n",
        (unsigned long)thisThread);
    return NULL;
}

void*	coder_process(void *c)
{
	t_coder	*wrapper;
	int					time;

	ft_printf("Hello");
	wrapper = (t_coder *)c;
	// Block the mutex

	// Loop as long as Active

	// Up status
	// usleep(wrapper->data->time_to_compile * 100);
	ft_printf("Hello %d\n", wrapper->remain);
	printf("Current thread ID: %lu\n", (unsigned long)pthread_self());

	// ft_lst_push_back(data->scheduler, t_list *new_node)

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

t_codexion	init_codexion(t_data data)
{
	t_codexion	codexion;
	int			counter;
	t_coder		new_coder;

	// Create an array of n dongles

	// Create an array of n threads
	codexion.coders = ft_calloc(data.number_of_coders, sizeof(t_coder));



	counter = data.number_of_coders;
	while (counter > 0)
	{
		// Create dongles

		// Affect them into coders
		new_coder = (t_coder){ .status=WAITING, .remain=data.nb_to_do, .data=&data };

	    // pthread_create(&(new_coder.thread), (void *)&new_coder, foo, NULL);
	    pthread_create(&(new_coder.thread), NULL, coder_process, (void *)&new_coder);
		codexion.coders[counter - 1] = new_coder;

		counter--;
	}

	return codexion;
}

void	close_codexion(t_data data, t_codexion codexion)
{
	// Loop in threads and wait them ?

	// Or set them has over ?
	while (data.number_of_coders > 0)
	{
		printf("join this one %d \n", data.number_of_coders);
		pthread_join(codexion.coders[data.number_of_coders - 1].thread, NULL);
		data.number_of_coders--;
	}

	free(codexion.coders);
}
