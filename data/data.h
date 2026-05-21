/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:19:38 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/21 21:41:56 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include <sys/time.h>

typedef struct s_data
{
	char			scheduler;
	int				nb_to_do;
	int				nb_coders;
	long			time_debug;
	long			time_burnout;
	long			time_compile;
	long			time_refact;
	long			time_cooldown;
	long			timestamp_start;
}	t_data;

#endif
