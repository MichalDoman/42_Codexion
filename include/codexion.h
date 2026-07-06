/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 10:38:32 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/06 10:14:16 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# define MAX_HEAP_SIZE 5

# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>

# include "codexion_types.h"
# include "heap.h"

// PARSING ----------------------------------------------------------
// core/parsing/validation.c:
int			validate_arguments(int argc, char **args);
// core/parsing/parsing.c:
int			parse_arguments(char **argv, t_config *config);

// SIMULATION -------------------------------------------------------
// core/simulation/simulation_init.c [4/5]:
int			sim_init(t_sim *sim, t_config *config);
// core/simulation/simulation_core.c [4/5]:
int			sim_is_running(t_sim *sim);
void		sim_stop(t_sim *sim);
void		sim_start(t_sim *sim);
void		sim_cleanup(t_sim *sim);
// core/simulation/threads.c [2/5]:
void		thread_wait_for_sim_ready(t_sim *sim);
void		thread_create_multi(t_sim *sim);
void		thread_join_multi(t_sim *sim);
// core/simulation/monitor.c [1/5]:
void		*monitor_routine(void *arg);
// core/simulation/coders.c [2/5]:
void		coder_set_start_time_multi(t_sim *sim);
void		*coder_routine(void *arg);
// core/simulation/time.c [1/5]:
long		get_time_ms(void);

// UTILS -----------------------------------------------------------------------
// utils/debugging:
void		print_config(t_config *config);
void		print_sim(t_sim *sim);

#endif