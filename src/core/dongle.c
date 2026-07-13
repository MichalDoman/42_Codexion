/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 14:13:40 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/13 15:38:43 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	dongle_is_available(t_dongle *dongle)
{
	if (dongle->coder_id != 0)
		return (0);
	if (dongle->next_availability_time > time_get_ms())
		return (0);
	return (1);
}

static void	dongle_lock_wait(t_dongle *dongle)
{
	timespec_t	wait_timeout;
	long		now;
	long		cooldown_end;

	now = time_get_ms();
	cooldown_end = dongle->next_availability_time;
	if (dongle->coder_id == 0 && cooldown_end > now)
	{
		wait_timeout = time_get_timespec(cooldown_end);
		pthread_cond_timedwait(&dongle->cond, &dongle->mutex, &wait_timeout);
	}
	else
		pthread_cond_wait(&dongle->cond, &dongle->mutex);
}

int	dongle_lock(t_dongle *dongle, t_sim *sim, int coder_id)
{
	t_heap_item	first;

	pthread_mutex_lock(&dongle->mutex);
	while (sim_is_running(sim))
	{
		if (dongle_is_available(dongle)
			&& heap_point_root(dongle->queue, &first)
			&& first.id == coder_id)
		{
			dongle->coder_id = coder_id;
			heap_remove(dongle->queue);
			pthread_mutex_unlock(&dongle->mutex);
			sim_log(sim, coder_id, "has taken a dongle");
			return (1);
		}
		dongle_lock_wait(dongle);
	}
	pthread_mutex_unlock(&dongle->mutex);
	return (0);
}

void	dongle_unlock(t_dongle *dongle, long cooldown)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->coder_id = 0;
	dongle->next_availability_time = time_get_ms() + cooldown;
	pthread_cond_broadcast(&dongle->cond);
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
		pthread_cond_destroy(&dongle->cond);
		pthread_mutex_destroy(&dongle->mutex);
		i++;
	}
	free(*dongles);
	*dongles = NULL;
}
