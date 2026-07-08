/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 09:58:11 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/08 20:13:42 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	coder_compile(t_coder *coder)
{
	t_sim	*sim;
	long	time_to_compile;

	sim = coder->sim;
	time_to_compile = coder->sim->config.time_to_compile;
	coder_lock_dongles(coder);
	pthread_mutex_lock(&sim->sim_mutex);
	coder->last_compile_start = time_get_ms();
	pthread_mutex_unlock(&sim->sim_mutex);
	sim_log(sim, coder->id, "is compiling");
	usleep(time_to_compile * 1000);
	pthread_mutex_lock(&sim->sim_mutex);
	coder->compile_count++;
	pthread_mutex_unlock(&sim->sim_mutex);
	coder_unlock_dongles(coder);
}

static void	coder_debug(t_coder *coder)
{
	long	time_to_debug;

	time_to_debug = coder->sim->config.time_to_debug;
	sim_log(coder->sim, coder->id, "is debugging");
	usleep(time_to_debug * 1000);
}

static void	coder_refactor(t_coder *coder)
{
	long	time_to_refactor;

	time_to_refactor = coder->sim->config.time_to_refactor;
	sim_log(coder->sim, coder->id, "is refactoring");
	usleep(time_to_refactor * 1000);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	thread_wait_for_sim_ready(coder->sim);
	while (sim_is_running(coder->sim))
	{
		coder_compile(coder);
		if (!sim_is_running(coder->sim))
			return (NULL);
		coder_debug(coder);
		if (!sim_is_running(coder->sim))
			return (NULL);
		coder_refactor(coder);
	}
	return (NULL);
}
