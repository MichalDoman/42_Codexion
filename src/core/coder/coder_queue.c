/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 10:10:22 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/13 10:49:12 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int coder_enqueue(t_dongle *dongle, t_coder *coder)
{
	t_heap_item	item;
	long		last_compile_start;
	long		time_to_burnout;
	long		priority;
	int			result;
	
	pthread_mutex_lock(&coder->sim->sim_mutex);
	last_compile_start = coder->last_compile_start;
	pthread_mutex_unlock(&coder->sim->sim_mutex);
	time_to_burnout = coder->sim->config.time_to_burnout;
	pthread_mutex_lock(&dongle->mutex);
	priority = coder->id;
	if (strcmp(coder->sim->config.scheduler, "fifo") == 0)
		priority = dongle->queue_order;
	else if (strcmp(coder->sim->config.scheduler, "edf") == 0)
		priority = last_compile_start + time_to_burnout;
	item.id = coder->id;
	item.value = priority;
	result = heap_push(dongle->queue, &item);
	if (strcmp(coder->sim->config.scheduler, "fifo") == 0 && result)
		dongle->queue_order++;
	pthread_mutex_unlock(&dongle->mutex);
	return (result);
}

void	coder_dequeue(t_dongle *dongle, t_coder *coder)
{
	pthread_mutex_lock(&dongle->mutex);
	heap_remove_by_id(dongle->queue, coder->id);
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}