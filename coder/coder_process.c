/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   coder_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 10:42:32 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/20 15:09:14 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

void	coder_process_print_status(t_coder_data *coder_data, t_coder *coder)
{
	int	time;

	pthread_mutex_lock(coder->mutex);
	time = get_time() - coder->data->timestamp_start;
	if (coder_data->status == COMPILING)
	{
		printf("%6d    C%-3d  has taken a dongle\n", time, coder->id);
		printf("%6d    C%-3d  has taken a dongle\n", time, coder->id);
		printf("%6d    C%-3d  is compiling (%d remain) 🤖\n", time, coder->id,
			coder_data->remain - 1);
	}
	else if (coder_data->status == DEBUGGING)
		printf("%6d    C%-3d  is debugging 🪲\n", time, coder->id);
	else if (coder_data->status == REFACTORING)
		printf("%6d    C%-3d  is refactoring 🧼\n", time, coder->id);
	else if (coder_data->status == BURNOUT)
		printf("%6d    C%-3d  🔥 has burned out 🔥\n", time, coder->id);
	pthread_mutex_unlock(coder->mutex);
}

void	coder_process_up_status(t_coder_data *coder_data,
			enum e_coder_status new_status,
			t_coder *coder)
{
	coder_data->status = new_status;
	coder_data->timestamp = get_time();
	if (new_status == COMPILING)
		coder_data->timestamp_last_comp = get_time();
	else if (new_status == WAITING)
	{
		coder_data->timestamp = get_time();
		coder_data->remain--;
	}
	coder_process_print_status(coder_data, coder);
}

void	coder_process_run(t_coder_data *coder_data, t_coder *coder)
{
	int	elapsed;

	elapsed = get_time() - coder_data->timestamp;
	if (coder_data->status == STARTING)
		coder_process_up_status(coder_data, COMPILING, coder);
	else if (coder_data->status == COMPILING
		&& elapsed > coder->data->time_compile)
		coder_process_up_status(coder_data, DEBUGGING, coder);
	else if (coder_data->status == DEBUGGING
		&& elapsed > coder->data->time_debug)
		coder_process_up_status(coder_data, REFACTORING, coder);
	else if (coder_data->status == REFACTORING
		&& elapsed > coder->data->time_refact)
		coder_process_up_status(coder_data, WAITING, coder);
	else if (coder_data->status == WAITING
		&& elapsed > coder->data->time_burnout)
		coder_process_up_status(coder_data, BURNOUT, coder);
}
