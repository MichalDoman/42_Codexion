/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 14:13:40 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/08 12:48:35 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	dongle_lock(t_dongle *dongle)
{
	
}

void	dongle_unlock(t_dongle *dongle)
{
	
}

int	dongle_is_available(t_dongle *dongle)
{

}


void	dongle_destroy_multi(t_dongle *dongles, int count)
{
	int 		i;
	t_dongle	*dongle;

	if (!dongles)
		return ;
	i = 0;
	while (i < count)
	{
		dongle = &dongles[i];
		if (dongle->queue)
			heap_free(dongle->queue);
		pthread_cond_destroy(&dongle->cond);
		pthread_mutex_destroy(&dongle->mutex);
		i++;
	}
	free(dongles);
}
