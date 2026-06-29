/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion_types.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 10:39:49 by mdomansk          #+#    #+#             */
/*   Updated: 2026/06/29 18:51:08 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_TYPES_H
# define CODEXION_TYPES_H

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

typedef struct s_coder
{
	int	id;
	int	l_dongle_id;
	int	r_dongle_id;
	
}	t_coder;

typedef struct s_dongle
{
	int	id;
	int	coder_id;
}	t_dongle;

typedef struct s_sim
{
	t_config	config;
	t_coder		*coders;
	t_dongle	*dongles;
	long		start_time;
}	t_sim;

#endif