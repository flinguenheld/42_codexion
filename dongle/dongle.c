/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:27:36 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/22 01:13:53 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dongle.h"

enum e_dongle_status	*init_dongles(t_data *data)
{
	int						index;
	enum e_dongle_status	*dongles;

	index = 0;
	dongles = malloc(data->nb_coders * sizeof(enum e_dongle_status));
	while (index < data->nb_coders)
	{
		dongles[index] = AVAILABLE;
		index++;
	}
	return (dongles);
}
