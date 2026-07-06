/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 09:58:17 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/06 13:34:54 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	thread_wait_for_sim_ready(t_sim *sim)
{
	pthread_mutex_lock(&sim->start_mutex);
	while (!sim->is_ready)
		pthread_cond_wait(&sim->start_cond, &sim->start_mutex);
	pthread_mutex_unlock(&sim->start_mutex);
}

void	thread_create_multi(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.number_of_coders)
	{
		pthread_create(
			&(sim->coders[i].thread),
			NULL,
			coder_routine,
			&(sim->coders[i])
		);
		i++;
	}
	pthread_create(
		&(sim->monitor_thread),
		NULL,
		monitor_routine,
		sim
	);
}

void	thread_join_multi(t_sim *sim)
{
	int		i;

	pthread_join(sim->monitor_thread, NULL);
	i = 0;
	while (i < sim->config.number_of_coders)
	{
		pthread_join((sim->coders[i]).thread, NULL);
		i++;
	}
}

