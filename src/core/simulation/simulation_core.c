/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 15:44:07 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/08 12:49:04 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	sim_is_running(t_sim *sim)
{
	int	result;

	pthread_mutex_lock(&sim->sim_mutex);
	result = sim->is_running;
	pthread_mutex_unlock(&sim->sim_mutex);
	return (result);
}

static void	sim_set_ready(t_sim *sim)
{
	pthread_mutex_lock(&sim->start_mutex);
	sim->start_time = time_get_ms();
	coder_set_start_time_multi(sim);
	sim->is_ready = 1;
	pthread_cond_broadcast(&sim->start_cond);
	pthread_mutex_unlock(&sim->start_mutex);
}

void	sim_start(t_sim *sim)
{
	thread_create_multi(sim);
	sim_set_ready(sim);
	thread_join_multi(sim);
	sim_cleanup(sim);
}

void	sim_stop(t_sim *sim)
{
	pthread_mutex_lock(&sim->sim_mutex);
	sim->is_running = 0;
	pthread_mutex_unlock(&sim->sim_mutex);
}

void	sim_cleanup(t_sim *sim)
{
	if (!sim)
		return ;
	if (sim->dongles)
	{
		dongle_destroy_multi(sim->dongles, sim->config.number_of_coders);
		sim->dongles = NULL;
	}
	if (sim->coders)
	{
		free(sim->coders);
		sim->coders = NULL;
	}
	pthread_mutex_destroy(&sim->sim_mutex);
	pthread_mutex_destroy(&sim->log_mutex);
	pthread_cond_destroy(&sim->start_cond);
	pthread_mutex_destroy(&sim->start_mutex);
}
