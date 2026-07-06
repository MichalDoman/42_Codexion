/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 10:20:34 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/06 10:16:09 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_config	config;
	t_sim		sim;

	if (!validate_arguments(argc, argv))
		return (1);
	if (!parse_arguments(argv, &config))
		return (1);
	if (!sim_init(&sim, &config))
		return (1);
	print_sim(&sim);
	sim_start(&sim);
	return (0);
}
