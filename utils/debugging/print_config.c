/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 10:26:34 by mdomansk          #+#    #+#             */
/*   Updated: 2026/06/29 10:26:54 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_config(t_config *config)
{
	if (!config)
		return ;
	printf("=== CONFIG DEBUG ===\n");
	printf("number_of_coders:             %d\n", config->number_of_coders);
	printf("time_to_burnout:              %d\n", config->time_to_burnout);
	printf("time_to_compile:              %d\n", config->time_to_compile);
	printf("time_to_debug:                %d\n", config->time_to_debug);
	printf("time_to_refactor:             %d\n", config->time_to_refactor);
	printf("number_of_compiles_required:  %d\n",
		config->number_of_compiles_required);
	printf("dongle_cooldown:              %d\n", config->dongle_cooldown);
	printf("scheduler:                    %s\n", config->scheduler);
	printf("====================\n");
}
