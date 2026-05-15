/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 15:19:38 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/15 15:19:39 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

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

#endif
