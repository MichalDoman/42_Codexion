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

int	coder_lock_dongles(t_coder *coder)
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
	coder_enqueue(first_dongle, coder);
	coder_enqueue(second_dongle, coder);
	if (!dongle_lock(first_dongle, coder->sim, coder->id))
		return (0);
	if (!dongle_lock(second_dongle, coder->sim, coder->id))
		return (dongle_unlock(first_dongle, 0), 0);
	return (1);
}

void	coder_unlock_dongles(t_coder *coder)
{
	long	cooldown;

	cooldown = coder->sim->config.dongle_cooldown;
	dongle_unlock(coder->left_dongle, cooldown);
	dongle_unlock(coder->right_dongle, cooldown);
}

int	coder_has_required_compiles(t_coder *coder)
{
	int	compile_count;
	int	compile_req;

	compile_req = coder->sim->config.number_of_compiles_required;
	if (compile_req <= 0)
		return (0);
	pthread_mutex_lock(&coder->sim->sim_mutex);
	compile_count = coder->compile_count;
	pthread_mutex_unlock(&coder->sim->sim_mutex);
	return (compile_count >= compile_req);
}
