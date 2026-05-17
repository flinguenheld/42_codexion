/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:43:34 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/17 23:49:59 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	get_overlapped_index(int index, int nb_elements)
{
	if (index < 0)
		return (nb_elements - 1);
	else if (index >= nb_elements - 1)
		return (0);
	else
		return (index);
}
