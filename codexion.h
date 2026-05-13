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
# include "sys/time.h"
# include "unistd.h"

enum e_status
{
	COMPILE,
	DEBUG,
	REFACTOR,
	COOLDOWN,
	WAITING,
};

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

typedef struct s_coder
{
	enum e_status	status;
	int				remain;
	int				id;
}	t_coder;

// Create a struct which regroups structs to feed coders ?
// Or add a pointer to data in coder ?

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
