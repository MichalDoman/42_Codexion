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

int	dongle_is_available(t_dongle *dongle)
{
	if (dongle->coder_id != 0)
		return (0);
	if (dongle->next_availability_time <= time_get_ms())
		return (0);
	return (1);
}

void	dongle_lock(t_dongle *dongle, int coder_id)
{
	while (!dongle_is_available(dongle))
		pthread_cond_wait(&dongle->cond, &dongle->mutex);
	dongle->coder_id = coder_id;
}

void	dongle_unlock(t_dongle *dongle, long cooldown)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->coder_id = 0;
	dongle->next_availability_time = time_get_ms() + cooldown;
	usleep(cooldown * 1000);
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
