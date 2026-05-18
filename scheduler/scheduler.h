/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   scheduler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 10:19:48 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/18 18:12:30 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCHEDULER_H
# define SCHEDULER_H

# include "../coder/coder.h"
# include "../dongle/dongle.h"

/**
 * @brief Copy coders which are waiting into the buffer.
 *        Coders which are not waiting are set to NONE.
 *        Preserve the amount of coders and their order.
 */
void	buffer_get_waiting_cd(t_coder **coders,
			t_coder **buffer,
			int nb_coders);

/**
 * @brief Loop into buffer and set to NULL coders which cannot be started
 *        due to the status of their dongles.
 */
void	buffer_filter(t_coder **buffer,
			enum e_dongle_status *dongles,
			int nb_coders);

/**
 * @brief Look for the index of the coder which has finished
 *        its compilation first.
 * @return coder index (buffer conserves the coder index) or -1 if None
 */
int		fifo(t_coder **buffer, int nb_coders);

/**
 * @brief Look for the index of the coder which is the closer to burn out.
 * @return coder index (buffer conserves the coder index) or -1 if None
 */
int		edf(t_coder **buffer, int nb_coders);

#endif
