/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 10:38:32 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/08 20:38:09 by mdomansk         ###   ########.fr       */
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

// PARSING --------------------------------------------------------------------
// src/parsing/validation.c [3/5]:
int			validate_arguments(int argc, char **args);

// src/parsing/parsing.c [1/5]:
int			parse_arguments(char **argv, t_config *config);

// SIMULATION -----------------------------------------------------------------
// src/core/simulation/simulation_init.c [5/5]:
int			sim_init(t_sim *sim, t_config *config);

// src/core/simulation/simulation_core.c [5/5]:
int			sim_is_running(t_sim *sim);
void		sim_start(t_sim *sim);
void		sim_stop(t_sim *sim);
void		sim_cleanup(t_sim *sim);

// src/core/simulation/simulation_misc.c [2/5]:
void		sim_log(t_sim *sim, int coder_id, char *msg);
void		sim_log_burnout(t_sim *sim, int coder_id, char *msg);

// src/core/threads.c [3/5]:
void		thread_wait_for_sim_ready(t_sim *sim);
void		thread_create_multi(t_sim *sim);
void		thread_join_multi(t_sim *sim);

// src/core/monitor.c [3/5]:
void		*monitor_routine(void *arg);

// src/core/dongle.c [5/5]:
int			dongle_is_available(t_dongle *dongle);
int			dongle_lock(t_dongle *dongle, t_sim *sim, int coder_id);
void		dongle_unlock(t_dongle *dongle, long cooldown);
void		dongle_destroy_multi(t_dongle **dongles, int count);

// src/core/coder/coder_routine.c [4/5]:
void		*coder_routine(void *arg);

// src/core/coder/coder_queue.c [2/5]:
void 		coder_enqueue(t_dongle *dongle, t_coder *coder);

// src/core/coder/coder_misc.c [4/5]:
void		coder_set_start_time_multi(t_sim *sim);
int			coder_lock_dongles(t_coder *coder);
void		coder_unlock_dongles(t_coder *coder);
int			coder_has_required_compiles(t_coder *coder);

// src/core/time.c [3/5]:
long		time_get_ms(void);
void		time_sleep(t_sim *sim, long duration);
timespec_t	time_get_timespec(long timestamp);

// UTILS ----------------------------------------------------------------------
// utils/debugging:
void		print_config(t_config *config);
void		print_sim(t_sim *sim);

#endif