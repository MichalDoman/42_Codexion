/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 10:27:16 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/08 10:21:03 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	print_coders(t_coder *coders, int number_of_coders)
{
	int	i;

	printf("\n--- CODERS ---\n");
	if (!coders)
	{
		printf("coders: NULL\n");
		return ;
	}
	i = 0;
	while (i < number_of_coders)
	{
		printf("coder[%d]: id=%d\n",
			i,
			coders[i].id
			);
		i++;
	}
}

static void	print_dongles(t_dongle *dongles, int number_of_dongles)
{
	int	i;

	printf("\n--- DONGLES ---\n");
	if (!dongles)
	{
		printf("dongles: NULL\n");
		return ;
	}
	i = 0;
	while (i < number_of_dongles)
	{
		printf("dongle[%d]: id=%d, coder_id=%d\n",
			i,
			dongles[i].id,
			dongles[i].coder_id);
		i++;
	}
}

void	print_sim(t_sim *sim)
{
	if (!sim)
	{
		printf("sim: NULL\n");
		return ;
	}
	printf("=== SIM DEBUG ===\n");
	print_config(&sim->config);
	print_coders(sim->coders, sim->config.number_of_coders);
	print_dongles(sim->dongles, sim->config.number_of_coders);
	printf("start_time: %ld\n\n", sim->start_time);
	printf("=================\n");
}
