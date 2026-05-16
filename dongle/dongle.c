/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:27:36 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/16 16:27:36 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dongle.h"

long	*init_dongles(t_data *data)
{
	int		index;
	long	*dongles;

	index = 0;
	dongles = malloc(data->nb_coders * sizeof(long));
	while (index < data->nb_coders)
	{
		dongles[index] = -1;
		index++;
	}
	return dongles;
}

/**
 * @brief Up one dongle value according to its left/right coders.
 */
static void	up_dongle(long *dongle, t_coder *cd_left,
							t_coder *cd_right, t_data *data)
{
	long	released_time;
	long	current_time;

	current_time = get_time();
	released_time = data->time_compile + data->time_cooldown;
	if (*dongle == -1)
	{
		if (current_time >= cd_left->timestamp_last_comp + released_time &&
			current_time >= cd_right->timestamp_last_comp + released_time)
		{
			*dongle = get_time();
		}
	}
	else if (cd_left->status == COMPILING || cd_right->status == COMPILING)
		*dongle = -1;
}

/**
 * @brief Loop in dongles to update their values according to coders.
 */
void up_dongles(long *dongles, t_coder **coders, t_data *data)
{
	int	dongle_index;
	int	coder_index[2];

	dongle_index = 0;
	while (dongle_index < data->nb_coders)
	{
		coder_index[0] = dongle_index;
		coder_index[1] = dongle_index + 1;
		if (coder_index[1] == data->nb_coders)
			coder_index[1] = 0;
		up_dongle(&dongles[dongle_index],
				coders[coder_index[0]],
				coders[coder_index[1]],
				data);

		dongle_index++;
	}
}
