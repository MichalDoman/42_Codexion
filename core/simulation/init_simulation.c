/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 10:33:42 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/01 10:34:40 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	init_coders(t_coder **coders, int number_of_coders)
{
	int	i;

	*coders = malloc(sizeof(t_coder) * number_of_coders);
	if (!*coders)
		return (0);
	i = 0;
	while (i < number_of_coders)
	{
		(*coders)[i].id = i + 1;
		(*coders)[i].l_dongle_id = i + 1;
		(*coders)[i].r_dongle_id = ((i + 1) % number_of_coders) + 1;
		i++;
	}
	return (1);
}

static int	init_dongles(t_dongle **dongles, int number_of_dongles)
{
	int	i;

	*dongles = malloc(sizeof(t_dongle) * number_of_dongles);
	if (!*dongles)
		return (0);
	i = 0;
	while (i < number_of_dongles)
	{
		(*dongles)[i].id = i + 1;
		(*dongles)[i].coder_id = 0;
		i++;
	}
	return (1);
}

int	init_simulation(t_sim *sim, t_config *config)
{
	if (!sim || !config)
		return (0);
	memset(sim, 0, sizeof(t_sim));
	sim->config = *config;
	if (!init_coders(&sim->coders, config->number_of_coders))
		return (0);
	if (!init_dongles(&sim->dongles, config->number_of_coders))
	{
		free(sim->coders);
		return (0);
	}
	sim->start_time = 0;
	return (1);
}
