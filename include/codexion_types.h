/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_types.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 10:39:49 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/06 10:32:54 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_TYPES_H
# define CODEXION_TYPES_H

# include <pthread.h>
# include "heap.h"

typedef struct s_sim	t_sim;

typedef struct s_config
{
	int		number_of_coders;
	int		time_to_burnout;
	int		time_to_compile;
	int		time_to_debug;
	int		time_to_refactor;
	int		number_of_compiles_required;
	int		dongle_cooldown;
	char	*scheduler;
}	t_config;

typedef struct s_dongle
{
	int				id;
	int				coder_id;
	long			cooldown_until;
	t_heap			*queue;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
}	t_dongle;

typedef struct s_coder
{
	int				id;
	int				compile_count;
	long			last_compile_time;
	pthread_t		thread;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	t_sim			*sim; // required for coder_routine()
}	t_coder;

typedef struct s_sim
{
	t_config		config;
	t_coder			*coders;
	t_dongle		*dongles;

	pthread_t		monitor_thread;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	sim_mutex;

	pthread_mutex_t	start_mutex;
	pthread_cond_t	start_cond;
	int				is_ready;
	int				is_running;
	long			start_time;
}	t_sim;

#endif
