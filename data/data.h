/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:19:38 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/15 23:17:17 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <sys/time.h>

typedef struct s_data
{
	char			scheduler;
	int				time_debug;
	int				time_burnout;
	int				time_compile;
	int				time_refact;
	int				time_cooldown;
	int				nb_to_do;
	int				nb_coders;
	long			timestamp_start;
}	t_data;

#endif
