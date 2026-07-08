/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 18:36:14 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/08 18:37:12 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	coder_set_start_time_multi(t_sim *sim)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&sim->sim_mutex);
	while (i < sim->config.number_of_coders)
	{
		sim->coders[i].last_compile_time = sim->start_time;
		i++;
	}
	pthread_mutex_unlock(&sim->sim_mutex);
}

void	coder_lock_dongles(t_coder *coder)
{
	
}

void	coder_unlock_dongles(t_coder *coder)
{
	
}