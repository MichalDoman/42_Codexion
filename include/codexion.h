/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 10:38:32 by mdomansk          #+#    #+#             */
/*   Updated: 2026/06/29 10:39:31 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <pthread.h>
# include <string.h>

# include "codexion_types.h"
# include "heap.h"

// PARSING ----------------------------------------------------------
// parsing/validation.c:
int			validate_arguments(int argc, char **args);
// parsing/parsing.c:
int			parse_arguments(char **argv, t_config *config);

// SIMULATION -------------------------------------------------------
// simulation/init_simulation.c:
int			init_simulation(t_sim *sim, t_config *config);

// UTILS ------------------------------------------------------------
// utils/debugging:
void		print_config(t_config *config);
void		print_sim(t_sim *sim);

#endif