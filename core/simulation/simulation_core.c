/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 15:44:07 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/01 16:31:22 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	*coder_routine(void *arg)
{

}

void	simulate(t_sim *sim)
{
	create_threads(sim);

	join_threads(sim);
	// destroy_stuff()
}
