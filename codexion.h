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
# include <pthread.h>
// #include <bits/pthreadtypes.h>
# include <stdio.h>

enum e_status
{
	COMPILING,
	DEBUGGING,
	REFACTORING,
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
	pthread_t		thread;
	t_data			*data;
	t_list			*to_print;
}	t_coder;

typedef struct s_codexion
{
	t_coder	*coders;
	t_list	*to_print;
}	t_codexion;

// Create a struct which regroups structs to feed coders ?
// Or add a pointer to data in coder ?

// ----------------------------------------------------------------------------
// --------------------------------------------------------------- CODEXION ---
/**
 * @brief
 */
t_codexion	init_codexion(t_data data);

/**
 * @brief
 */
void	close_codexion(t_data data, t_codexion codexion);

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
