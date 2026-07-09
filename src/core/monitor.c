/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 09:58:13 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/08 20:29:10 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	monitor_burnout(t_sim *sim)
{
	int		i;
	long	compile_start_time;
	long	time_since_compile_start;

	i = 0;
	while (i < sim->config.number_of_coders)
	{
		pthread_mutex_lock(&sim->sim_mutex);
		compile_start_time = sim->coders[i].last_compile_start;
		pthread_mutex_unlock(&sim->sim_mutex);
		time_since_compile_start = (time_get_ms() - compile_start_time);
		if (time_since_compile_start >= sim->config.time_to_burnout)
		{
			sim_log_burnout(sim, i + 1, "burned out");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	monitor_compile_count(t_sim *sim)
{
	int		i;
	int		compiles_req;
	int		compile_count;

	i = 0;
	compiles_req = sim->config.number_of_compiles_required;
	while (i < sim->config.number_of_coders)
	{
		pthread_mutex_lock(&sim->sim_mutex);
		compile_count = sim->coders[i].compile_count;
		pthread_mutex_unlock(&sim->sim_mutex);
		if (compile_count < compiles_req)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)arg;
	thread_wait_for_sim_ready(sim);
	while (sim_is_running(sim))
	{
		if (monitor_burnout(sim))
			return (sim_stop(sim), NULL);
		if (monitor_compile_count(sim))
			return (sim_stop(sim), NULL);
		usleep(500);
	}
	return (NULL);
}
