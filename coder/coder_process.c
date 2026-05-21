/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   coder_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flinguen <florent@linguenheld.net>          +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 10:42:32 by flinguen          #+#    #+#             */
/*   Updated: 2026/05/22 01:13:53 by flinguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder.h"

/**
 * @brief Print the time from start and the the coder ID (no mutex !)
 */
static void	print_header(t_coder *coder)
{
	int	time;

	time = (get_time() - coder->data->timestamp_start) / 1000;
	printf("%6d    C%-3d  ", time, coder->id);
}

void	coder_process_print_status(t_coder_data *coder_data, t_coder *coder)
{
	pthread_mutex_lock(coder->mutexes.stdout);
	print_header(coder);
	if (coder_data->status == COMPILING)
	{
		printf("╭──▶ has taken a dongle\n");
		printf("                ╰──▶ has taken a dongle\n");
		printf("                is compiling (remain %d) 🤖\n",
			coder_data->remain - 1);
	}
	else if (coder_data->status == DONE)
		printf("✅️ done ✅️\n");
	else if (coder_data->status == DEBUGGING)
		printf("is debugging 🪲\n");
	else if (coder_data->status == REFACTORING)
		printf("is refactoring 🧼\n");
	else if (coder_data->status == WAITING)
		printf("is waiting 💤\n");
	else if (coder_data->status == BURNOUT)
		printf("🔥 has burned out 🔥\n");
	else if (coder_data->status == KILLED)
		printf("💀 killed 💀\n");
	pthread_mutex_unlock(coder->mutexes.stdout);
}

void	coder_process_up_status(t_coder_data *coder_data,
			enum e_coder_status new_status,
			t_coder *coder)
{
	coder_data->status = new_status;
	coder->timestamp_process = get_time();
	if (new_status == COMPILING)
		coder_data->timestamp_last_comp = get_time();
	else if (new_status == DEBUGGING)
		coder->timestamp_release_dongles = get_time();
	else if (new_status == WAITING)
	{
		coder->timestamp_process = get_time();
		coder_data->remain--;
		if (coder_data->remain <= 0)
			coder_data->status = DONE;
	}
	coder_process_print_status(coder_data, coder);
}

/**
 * @brief Check if dongles have to be released.
 *        If so, release them (using dongle mutex)
 *        and print the action (using stdout mutex)
 */
static void	release_dongles(t_coder *coder)
{
	if (coder->timestamp_release_dongles > 0)
	{
		if (get_time() - coder->timestamp_release_dongles
			>= coder->data->time_cooldown)
		{
			coder->timestamp_release_dongles = 0;
			pthread_mutex_lock(coder->mutexes.dongles);
			*(coder->dongles.left) = AVAILABLE;
			*(coder->dongles.right) = AVAILABLE;
			pthread_mutex_unlock(coder->mutexes.dongles);
			pthread_mutex_lock(coder->mutexes.stdout);
			print_header(coder);
			printf("◀──╮ has released a dongle\n");
			printf("                ◀──╯ has released a dongle\n");
			pthread_mutex_unlock(coder->mutexes.stdout);
		}
	}
}

void	coder_process_run(t_coder_data *coder_data, t_coder *coder)
{
	int	elapsed;

	elapsed = get_time() - coder->timestamp_process;
	release_dongles(coder);
	if (coder_data->status == KILLED)
		coder_process_print_status(coder_data, coder);
	else if (coder_data->status == STARTING)
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
