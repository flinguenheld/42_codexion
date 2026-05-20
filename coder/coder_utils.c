/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   coder_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 18:16:11 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/20 15:36:52 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

t_coder	*new_coder(t_data *data,
		pthread_mutex_t *mutex,
		pthread_mutex_t *mutex_stdout,
		int id)
{
	t_coder		*new_coder;

	new_coder = malloc(sizeof(t_coder));
	new_coder->mutex = mutex;
	new_coder->mutex_stdout = mutex_stdout;
	new_coder->data = data;
	new_coder->message = NONE;
	new_coder->id = id;
	new_coder->coder_data = (t_coder_data){
		.status = WAITING,
		.timestamp_last_comp = -1,
		.timestamp = get_time(),
		.remain = data->nb_to_do
	};
	return (new_coder);
}
