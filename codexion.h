/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 19:14:19 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/17 23:49:58 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include "coder/coder.h"
# include "data/data.h"
# include "parser/parser.h"
# include "dongle/dongle.h"

typedef struct s_codexion
{
	t_coder					**coders;
	t_coder					**buffer;
	enum e_dongle_status	*dongles;
	pthread_mutex_t			*mutex;
}	t_codexion;

// Create a struct which regroups structs to feed coders ?
// Or add a pointer to data in coder ?

// ----------------------------------------------------------------------------
// --------------------------------------------------------------- CODEXION ---

/**
 * @brief
 */
t_codexion		init_codexion(t_data *data);

/**
 * @brief Cleanly close codexion
 */
void			close_codexion(t_data *data, t_codexion codexion);

// ----------------------------------------------------------------------------
// ------------------------------------------------------------------ USAGE ---

/**
 * @brief
 * Print the usage message
 * error = 1 to print in stderr
 */
void			usage(int error);

#endif
