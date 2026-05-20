/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:27:36 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/20 15:09:15 by flinguen         ###   ########.fr       */
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

// ----------------------------------------------------------------------------
// ------------------------------------------------------------- UP DONGLES ---

/**
 * @brief Up one dongle value according to its left/right coders.
 *        Required an active mutex on coders!
 */
static void	up_a_dongle(enum e_dongle_status *dongle,
					t_coder *cd_left,
					t_coder *cd_right,
					long released_time)
{
	long	now;

	now = get_time();
	if (*dongle == BUSY)
	{
		if (cd_left->coder_data.status != STARTING
			&& cd_right->coder_data.status != STARTING)
		{
			if (now >= cd_left->coder_data.timestamp_last_comp + released_time
				&& now
				>= cd_right->coder_data.timestamp_last_comp + released_time)
			{
				*dongle = AVAILABLE;
			}
		}
	}
}

void	up_dongles(enum e_dongle_status *dongles,
					t_coder **coders,
					t_data *data,
					pthread_mutex_t *mutex)
{
	long	released_time;
	int		dongle_index;

	released_time = data->time_compile + data->time_cooldown;
	dongle_index = 0;
	pthread_mutex_lock(mutex);
	while (dongle_index < data->nb_coders)
	{
		up_a_dongle(&dongles[dongle_index],
			coders[dongle_index],
			coders[get_overlapped_index(dongle_index + 1, data->nb_coders)],
			released_time);
		dongle_index++;
	}
	pthread_mutex_unlock(mutex);
}
