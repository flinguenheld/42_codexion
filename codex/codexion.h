/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 19:14:19 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/20 15:36:52 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include "../data/data.h"
# include "../coder/coder.h"
# include "../parser/parser.h"
# include "../dongle/dongle.h"

/**
 * @brief - coders: array of coders (one thread per coder)
 *        - buffer: array of coders (same size), used by the scheduler to
 *                  list and filter available coders.
 *        - dongles: array of dongles (same size), used to set the dongles
 *                  status. Their index set their position in the circle.
 *        - mutex
 */
typedef struct s_codexion
{
	t_coder					**coders;
	t_coder					**buffer;
	enum e_dongle_status	*dongles;
	pthread_mutex_t			*mutex_coders;
	pthread_mutex_t			*mutex_stdout;
}	t_codexion;

// ----------------------------------------------------------------------------
// ----------------------------------------------------------- OPEN / CLOSE ---

/**
 * @brief Create a struct t_codexion and fill it according to the given data.
 *        Malloc and init coders, buffers, dongles, mutexes
 *        Launch threads (coders)
 *
 *        Use the 'close_codexion' function to free everything.
 */
t_codexion	init_codexion(t_data *data);

/**
 * @brief Cleanly close codexion.
 *        Free all pointers openned by 'init_codexion'.
 */
void		close_codexion(t_data *data, t_codexion codexion);

/**
 * @brief Core of codexion.
 *        Loop untils all coders are done or one has burned out
 *        (kill all others in this case)
 *
 *        Try to find the next coder to start on each turn.
 *        Send a message to start it in this case and update dongle status.
 */
void		run(t_codexion *codexion, t_data *data);

// ----------------------------------------------------------------------------
// ------------------------------------------------------------------ UTILS ---

/**
 * @brief Loop in coders to check their status and their remaining.
 * @return 0 -> there are still active coders
 *         1 -> all coders are done
 *         2 -> One coder has burned out
 */
char		are_all_coders_done(t_coder **coders,
				t_data *data,
				pthread_mutex_t *mutex);

/**
 * @brief Send the KILLED message to all coders.
 *        (using mutex)
 */
void		kill_all_coders(t_coder **coders,
				t_data *data,
				pthread_mutex_t *mutex);

#endif
