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

static int	coder_compile(t_coder *coder)
{
	t_sim	*sim;
	long	time_to_compile;

	sim = coder->sim;
	time_to_compile = coder->sim->config.time_to_compile;
	if (!coder_lock_dongles(coder))
		return (0);
	pthread_mutex_lock(&sim->sim_mutex);
	coder->last_compile_start = time_get_ms();
	pthread_mutex_unlock(&sim->sim_mutex);
	sim_log(sim, coder->id, "is compiling");
	time_sleep(coder->sim, time_to_compile);
	pthread_mutex_lock(&sim->sim_mutex);
	coder->compile_count++;
	pthread_mutex_unlock(&sim->sim_mutex);
	coder_unlock_dongles(coder);
	return (1);
}

static void	coder_debug(t_coder *coder)
{
	long	time_to_debug;

	time_to_debug = coder->sim->config.time_to_debug;
	sim_log(coder->sim, coder->id, "is debugging");
	time_sleep(coder->sim, time_to_debug);
}

static void	coder_refactor(t_coder *coder)
{
	long	time_to_refactor;

	time_to_refactor = coder->sim->config.time_to_refactor;
	sim_log(coder->sim, coder->id, "is refactoring");
	time_sleep(coder->sim, time_to_refactor);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	thread_wait_for_sim_ready(coder->sim);
	while (sim_is_running(coder->sim) && !coder_has_required_compiles(coder))
	{
		if (!coder_compile(coder))
			continue ;
		if (!sim_is_running(coder->sim) || coder_has_required_compiles(coder))
			return (NULL);
		coder_debug(coder);
		if (!sim_is_running(coder->sim))
			return (NULL);
		coder_refactor(coder);
	}
	return (NULL);
}
