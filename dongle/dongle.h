/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   dongle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:27:36 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/17 23:49:59 by flinguen         ###   ########.fr       */
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
 * @brief Since dongles are in a circle, the dongle index max + 1 has to be 0.
 * @return The checked index
 */
int						overlap_dongle_index(int index, long *dongles,
							t_data *data);

/**
 * @brief Malloc an array of longs and init all values to -1.
 * @return A brand new array to free
 */
enum e_dongle_status	*init_dongles(t_data *data);

/**
 * @brief 
 * @return 
 */
void					up_dongles(enum e_dongle_status *dongles,
							t_coder **coders, t_data *data);

#endif
