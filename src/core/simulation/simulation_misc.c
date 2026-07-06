/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_misc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 13:46:37 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/06 13:52:19 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	sim_log(t_sim *sim, int coder_id, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(sim->log_mutex);
	timestamp = time_get_ms() - sim->start_time;
	printf("%ld %d %s\n", timestamp, coder_id, msg);	
	pthread_mutex_unlock(sim->log_mutex);
}