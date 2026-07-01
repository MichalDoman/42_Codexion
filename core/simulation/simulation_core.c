/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 15:44:07 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/01 16:31:22 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	*coder_routine(void *arg)
{

}

void	simulate(t_sim *sim)
{
	int			i;
	t_coder		coder;

	i = 0;
	while (i < sim->config.number_of_coders)
	{
		coder = sim->coders[i];
		pthread_create(&(coder->thread), NULL, coder_routine, &coder)
		i++;
	}

	i = 0;
	while (i < sim->config.number_of_coders)
	{
		pthread_join((sim->coders[i]).thread, NULL);
		i++;
	}
	// pthread_join(monitor_thread, NULL);
	// destroy_stuff()
}
