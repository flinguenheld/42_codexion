/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   dongle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:27:36 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/22 01:13:53 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLE_H
# define DONGLE_H

# include "../data/data.h"
# include <stdlib.h>

enum e_dongle_status
{
	AVAILABLE,
	BUSY,
};

/**
 * @brief Malloc an array of dongle_status enum and init
 *        all values to AVAILABLE.
 *        There are as many coders than dongles (their index is important).
 * @return A brand new array to free
 */
enum e_dongle_status	*init_dongles(t_data *data);

#endif
