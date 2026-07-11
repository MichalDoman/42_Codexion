/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 10:33:42 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/08 20:28:16 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	init_dongle(t_dongle *dongle, int id, char *scheduler)
{
	dongle->id = id;
	dongle->coder_id = 0;
	dongle->next_availability_time = 0;
	dongle->queue_order = 0;
	dongle->queue = NULL;
	dongle_create_queue(dongle, scheduler);
	if (!dongle->queue)
		return (0);
	if (pthread_cond_init(&dongle->cond, NULL) != 0)
		return (heap_free(dongle->queue), 0);
	if (pthread_mutex_init(&dongle->mutex, NULL) != 0)
	{
		pthread_cond_destroy(&dongle->cond);
		heap_free(dongle->queue);
		return (0);
	}
	return (1);
}

static int	init_dongles(
	t_dongle **dongles,
	int number_of_dongles,
	char *scheduler)
{
	int	i;

	*dongles = malloc(sizeof(t_dongle) * number_of_dongles);
	if (!*dongles)
		return (0);
	i = 0;
	while (i < number_of_dongles)
	{
		if (!init_dongle(&(*dongles)[i], i + 1, scheduler))
			return (dongle_destroy_multi(dongles, i), 0);
		i++;
	}
	return (1);
}

static int	init_coders(t_coder **coders, t_sim *sim)
{
	int		i;
	int		number_of_coders;
	t_coder	*coder;

	number_of_coders = sim->config.number_of_coders;
	*coders = malloc(sizeof(t_coder) * number_of_coders);
	if (!*coders)
		return (0);
	i = 0;
	while (i < number_of_coders)
	{
		coder = &(*coders)[i];
		coder->id = i + 1;
		coder->compile_count = 0;
		coder->last_compile_start = sim->start_time;
		coder->left_dongle = &sim->dongles[i];
		coder->right_dongle = &sim->dongles[(i + 1) % number_of_coders];
		coder->sim = sim;
		i++;
	}
	return (1);
}

static int	init_mutexes(t_sim *sim)
{
	if (pthread_mutex_init(&sim->start_mutex, NULL) != 0)
		return (0);
	if (pthread_cond_init(&sim->start_cond, NULL) != 0)
	{
		pthread_mutex_destroy(&sim->start_mutex);
		return (0);
	}
	if (pthread_mutex_init(&sim->log_mutex, NULL) != 0)
	{
		pthread_cond_destroy(&sim->start_cond);
		pthread_mutex_destroy(&sim->start_mutex);
		return (0);
	}
	if (pthread_mutex_init(&sim->sim_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&sim->log_mutex);
		pthread_cond_destroy(&sim->start_cond);
		pthread_mutex_destroy(&sim->start_mutex);
		return (0);
	}
	return (1);
}

/*
"sim->is_ready" is set to 1 and "start_time", 
are calculated after all threads are ready.
*/
int	sim_init(t_sim *sim, t_config *config)
{
	if (!sim || !config)
		return (0);
	memset(sim, 0, sizeof(t_sim));
	sim->config = *config;
	sim->is_ready = 0;
	sim->start_time = 0;
	sim->is_running = 1;
	if (!init_mutexes(sim))
		return (0);
	if (!init_dongles(
			&sim->dongles,
			config->number_of_coders,
			config->scheduler))
		return (sim_cleanup(sim), 0);
	if (!init_coders(&sim->coders, sim))
		return (sim_cleanup(sim), 0);
	return (1);
}
