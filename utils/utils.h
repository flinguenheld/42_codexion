/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 17:43:34 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/20 15:09:15 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

/**
 * @brief Get the current time whit the gettimeofday function.
 * @return time in milliseconds
 */
long	get_time(void);

/**
 * @brief Fit the given index to the size of an array of nb_elements.
 *        And overlap if index is out of boundaries.
 * @return nb_elements-1, 0 or index
 */
int		get_overlapped_index(int index, int nb_elements);

/**
 * @brief
 * Print the usage message
 * error = 1 to print in stderr
 */
void	usage(int error);

#endif
