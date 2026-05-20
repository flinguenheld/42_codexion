/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   dongle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:27:36 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/20 15:09:15 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLE_H
# define DONGLE_H

# include "../data/data.h"
# include "../coder/coder.h"

enum e_dongle_status
{
	BUSY,
	AVAILABLE,
};

/**
 * @brief Malloc an array of dongle_status enum and init
 *        all values to AVAILABLE.
 *        There are as many coders than dongles (their index is important).
 * @return A brand new array to free
 */
enum e_dongle_status	*init_dongles(t_data *data);

/**
 * @brief Loop in dongles to update their status according to coders.
 *        A dongle is surrounded by two coders
 *        So get them and check their status and their last compilation time.
 *        (uses a mutex to lock coders)
 */
void					up_dongles(enum e_dongle_status *dongles,
							t_coder **coders,
							t_data *data,
							pthread_mutex_t *mutex);

#endif
