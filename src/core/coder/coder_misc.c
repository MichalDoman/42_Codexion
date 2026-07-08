/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 18:36:14 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/08 20:14:22 by mdomansk         ###   ########.fr       */
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
		sim->coders[i].last_compile_start = sim->start_time;
		i++;
	}
	pthread_mutex_unlock(&sim->sim_mutex);
}

void	coder_lock_dongles(t_coder *coder)
{
	t_dongle	*first_dongle;
	t_dongle	*second_dongle;

	first_dongle = coder->right_dongle;
	second_dongle = coder->left_dongle;
	if (coder->id % 2 == 0)
	{
		first_dongle = coder->left_dongle;
		second_dongle = coder->right_dongle;
	}
	pthread_mutex_lock(&first_dongle->mutex);
	dongle_lock(first_dongle, coder->id);
	pthread_mutex_lock(&second_dongle->mutex);
	dongle_lock(second_dongle, coder->id);
	pthread_mutex_unlock(&second_dongle->mutex);
	pthread_mutex_unlock(&first_dongle->mutex);
}

void	coder_unlock_dongles(t_coder *coder)
{
	long	cooldown;

	cooldown = coder->sim->config.dongle_cooldown;
	dongle_unlock(coder->left_dongle, cooldown);
	dongle_unlock(coder->right_dongle, cooldown);
}
