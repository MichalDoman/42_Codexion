/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 09:58:13 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/06 11:23:39 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	monitor_burnout(t_sim *sim)
{
	
}

int monitor_compile_count(t_sim *sim)
{
	
}

void	*monitor_routine(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)arg;
	thread_wait_for_sim_ready(sim);
	while (sim_is_running(sim))
	{
		if (monitor_burnout(sim))
			return (NULL);
		if (monitor_compile_count(sim))
		{
			pthread_mutex_lock(&im->sim_mutex);
			sim->is_running = 0;
			pthread_mutex_unlock(&sim->sim_mutex);
			return (NULL);
		}
		usleep(250);
	}
	return (NULL);
}