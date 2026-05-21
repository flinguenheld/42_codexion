/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   coder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 18:16:11 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/21 21:41:56 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

t_coder	*new_coder(t_data *data, t_mutexes mutexes, int id)
{
	t_coder		*new_coder;

	new_coder = malloc(sizeof(t_coder));
	new_coder->mutexes = mutexes;
	new_coder->message = NONE;
	new_coder->data = data;
	new_coder->id = id;
	new_coder->coder_data = (t_coder_data){
		.status = WAITING,
		.timestamp_last_comp = -1,
		.timestamp = get_time(),
		.remain = data->nb_to_do
	};
	return (new_coder);
}

void	coder_attach_dongles(t_coder *coder,
		char	*dongle_left,
		char	*dongle_right,
		pthread_mutex_t *mutex)
{
	coder->dongles.left = dongle_left;
	coder->dongles.right = dongle_right;
	coder->dongles.mutex = mutex;
}
