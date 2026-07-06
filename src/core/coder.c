/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 09:58:11 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/06 13:55:24 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	coder_set_start_time_multi(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.number_of_coders)
	{
		sim->coders[i].last_compile_time = sim->start_time;
		i++;
	}
}

void	coder_compile(t_coder *coder)
{
	long	time_to_compile;

	time_to_compile = coder->sim->config.time_to_compile;
}

void	coder_debug(t_coder *coder)
{
	long	time_to_debug;

	time_to_debug = coder->sim->config.time_to_debug;
	sim_log(coder->sim, coder->id, "is debugging");
	usleep(time_to_debug);
}

void	coder_refactor(t_coder *coder)
{
	long	time_to_refactor;

	time_to_refactor = coder->sim->config.time_to_refactor;
	sim_log(coder->sim, coder->id, "is refactoring");
	usleep(time_to_refactor);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	thread_wait_for_sim_ready(coder->sim);
	while(sim_is_running(coder->sim))
	{
		if (!sim_is_running(coder->sim))
			return (NULL);
		while (sim_is_running(coder->sim))
		{
			coder_compile(coder);
			coder_debug(coder);
			coder_refactor(coder);
		}
	}
	return (NULL);
}