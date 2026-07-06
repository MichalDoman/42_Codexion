/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 10:35:48 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/01 10:30:57 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	validate_integer(char *arg)
{
	int		i;
	long	value;

	i = 0;
	value = 0;
	if (!arg || !arg[i])
		return (0);
	if (arg[i] == '+')
		i++;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
		value = value * 10 + (arg[i] - '0');
		if (value > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

static int	validate_scheduler(char *arg)
{
	return (strcmp(arg, "fifo") == 0 || strcmp(arg, "edf") == 0);
}

int	validate_arguments(int argc, char **args)
{
	int	i;

	i = 1;
	if (argc != 9)
		return (0);
	while (i < 8)
	{
		if (!validate_integer(args[i]))
			return (0);
		i++;
	}
	if (!validate_scheduler(args[i]))
		return (0);
	return (1);
}
