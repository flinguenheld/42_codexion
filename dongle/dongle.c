/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:27:36 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/18 18:12:30 by flinguen         ###   ########.fr       */
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
	long	now_time;
	long	released_time;

	now_time = get_time();
	released_time = data->time_compile + data->time_cooldown;
	if (*dongle == BUSY)
	{
		// TODO: Add mutex ------------------------------------------------------------------
		// TODO: Add mutex ------------------------------------------------------------------
		// TODO: Add mutex ------------------------------------------------------------------
		// TODO: Add mutex ------------------------------------------------------------------

		pthread_mutex_lock(cd_left->mutex);
		if (cd_left->coder_data.status != STARTING && cd_right->coder_data.status != STARTING)
		{
			if (now_time >= cd_left->coder_data.timestamp_last_comp + released_time
				&& now_time >= cd_right->coder_data.timestamp_last_comp + released_time)
			{
				*dongle = AVAILABLE;
			}
		}
		pthread_mutex_unlock(cd_left->mutex);
	}
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
