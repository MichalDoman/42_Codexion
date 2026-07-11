/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 14:13:40 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/08 20:22:32 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	dongle_create_queue(t_dongle *dongle, char *scheduler)
{
	if (strcmp(scheduler, "fifo") == 0)
		dongle->queue = heap_init(MAX_HEAP_SIZE, 0);
	else if (strcmp(scheduler, "edf") == 0)
		dongle->queue = heap_init(MAX_HEAP_SIZE, 1);
}

int	dongle_is_available(t_dongle *dongle)
{
	if (dongle->coder_id != 0)
		return (0);
	if (dongle->next_availability_time > time_get_ms())
		return (0);
	return (1);
}

int	dongle_lock(t_dongle *dongle, t_sim *sim, int coder_id)
{
	while (sim_is_running(sim))
	{
		pthread_mutex_lock(&dongle->mutex);
		if (dongle_is_available(dongle))
		{
			dongle->coder_id = coder_id;
			pthread_mutex_unlock(&dongle->mutex);
			sim_log(sim, coder_id, "has taken a dongle");
			return (1);
		}
		pthread_mutex_unlock(&dongle->mutex);
		usleep(500);
	}
	return (0);
}

void	dongle_unlock(t_dongle *dongle, long cooldown)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->coder_id = 0;
	dongle->next_availability_time = time_get_ms() + cooldown;
	pthread_mutex_unlock(&dongle->mutex);
}

void	dongle_destroy_multi(t_dongle **dongles, int count)
{
	int			i;
	t_dongle	*dongle;

	if (!dongles || !*dongles)
		return ;
	i = 0;
	while (i < count)
	{
		dongle = &(*dongles)[i];
		if (dongle->queue)
			heap_free(dongle->queue);
		pthread_mutex_destroy(&dongle->mutex);
		i++;
	}
	free(*dongles);
	*dongles = NULL;
}
