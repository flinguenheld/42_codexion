/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 19:14:19 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/12 19:14:19 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include "libft/libft.h"

typedef struct s_data
{
	int		number_of_coders;
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		nb_to_do;
	int		dongle_cooldown;
	char	scheduler;
}	t_data;

// ----------------------------------------------------------------------------
// ------------------------------------------------------------------ USAGE ---
/**
 * @brief
 * Print the usage message
 * error = 1 to print in stderr
 */
void	usage(int error);

// ----------------------------------------------------------------------------
// ------------------------------------------------------------------ PARSE ---
/**
 * @brief
 * Parse the given arguments to fill data.
 * @return 0 if ok or the amount of wrong arguments
 */
char	parse(int argc, char **argv, t_data *data);

#endif
