/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 09:56:56 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/08 20:19:57 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	time_get_ms(void)
{
	struct timeval	tv;
	long			seconds;
	long			milliseconds;
	long			microseconds;

	gettimeofday(&tv, NULL);
	seconds = (long)tv.tv_sec;
	microseconds = (long)tv.tv_usec;
	milliseconds = seconds * 1000 + microseconds / 1000;
	return (milliseconds);
}

void	time_sleep(t_sim *sim, long duration)
{
	long	start;

	start = time_get_ms();
	while (sim_is_running(sim) && time_get_ms() - start < duration)
		usleep(500);
}
