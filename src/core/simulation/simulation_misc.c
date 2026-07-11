/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_misc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 13:46:37 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/08 12:01:13 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	sim_log(t_sim *sim, int coder_id, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&sim->log_mutex);
	if (sim_is_running(sim))
	{
		timestamp = time_get_ms() - sim->start_time;
		printf("%ld %d %s\n", timestamp, coder_id, msg);
	}
	pthread_mutex_unlock(&sim->log_mutex);
}

void	sim_log_burnout(t_sim *sim, int coder_id, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&sim->log_mutex);
	if (sim_is_running(sim))
	{
		timestamp = time_get_ms() - sim->start_time;
		printf("%ld %d %s\n", timestamp, coder_id, msg);
		sim_stop(sim);
	}
	pthread_mutex_unlock(&sim->log_mutex);
}

void	sim_broadcast_all(t_sim *sim)
{
	int			i;
	t_dongle	&dongle;

	i = 0;
	while (i < sim->config.number_of_coders)
	{
		dongle = &sim->dongles[i];
		pthread_mutex_lock(&dongle->mutex);
		pthread_cond_broadcast(&dongle->cond);
		pthread_mutex_unlock(&dongle->mutex);
		i++;
	}
}