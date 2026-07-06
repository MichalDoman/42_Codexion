/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 15:44:07 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/06 10:15:44 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	sim_is_running(t_sim *sim)
{
	int	result;

	pthread_mutex_lock(&sim->state_mutex);
	result = sim->is_running;
	pthread_mutex_unlock(&sim->state_mutex);
	return (result);
}

void	sim_stop(t_sim *sim)
{
	pthread_mutex_lock(&sim->state_mutex);
	sim->is_running = 0;
	pthread_mutex_unlock(&sim->state_mutex);
}

void	sim_start(t_sim *sim)
{
	create_threads(sim);
	join_threads(sim);
	sim_cleanup(sim);
}

void	sim_cleanup(t_sim *sim)
{
	if (!sim)
		return ;
	free(sim->dongles);
	free(sim->coders);
	pthread_mutex_destroy(&sim->state_mutex);
	pthread_mutex_destroy(&sim->log_mutex);
	pthread_cond_destroy(&sim->start_cond);
	pthread_mutex_destroy(&sim->start_mutex);
}
