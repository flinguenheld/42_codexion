/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:43:34 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/15 17:43:34 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_usec / 1000);
}
