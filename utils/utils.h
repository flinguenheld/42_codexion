/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:43:34 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/15 17:43:34 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <sys/time.h>

/**
 * @brief Get the current time whit the gettimeofday function.
 * @return time in milliseconds
 */
int	get_time(void);

#endif
