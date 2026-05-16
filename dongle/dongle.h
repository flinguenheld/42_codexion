/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   dongle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 16:27:36 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/16 16:27:36 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLE_H
# define DONGLE_H

# include "../data/data.h"
# include "../coder/coder.h"

/**
 * @brief Malloc an array of longs and init all values to -1.
 * @return A brand new array to free
 */
long	*init_dongles(t_data *data);

/**
 * @brief 
 * @return 
 */
void up_dongles(long *dongles, t_coder **coders, t_data *data);

#endif
