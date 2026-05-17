/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:27:36 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/17 23:49:59 by flinguen         ###   ########.fr       */
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

/**
 * @brief Up one dongle value according to its left/right coders.
 */
static void	up_dongle(enum e_dongle_status *dongle, t_coder *cd_left,
							t_coder *cd_right, t_data *data)
{
	long	released;
	long	current;

	current = get_time();
	released = data->time_compile + data->time_cooldown;
	if (*dongle == BUSY)
	{
		if (cd_left->status != START && cd_right->status != START)
		{
			if (current >= cd_left->timestamp_last_comp + released
				&& current >= cd_right->timestamp_last_comp + released)
			{
				*dongle = AVAILABLE;
			}
		}
	}
	else if (cd_left->status == COMPILING || cd_right->status == COMPILING)
		*dongle = BUSY;
}

/**
 * @brief Loop in dongles to update their values according to coders.
 */
void	up_dongles(enum e_dongle_status *dongles,
				t_coder **coders, t_data *data)
{
	int	dongle_index;

	dongle_index = 0;
	while (dongle_index < data->nb_coders)
	{
		up_dongle(&dongles[dongle_index],
			coders[dongle_index],
			coders[get_overlapped_index(dongle_index + 1, data->nb_coders)],
			data);
		dongle_index++;
	}
}
