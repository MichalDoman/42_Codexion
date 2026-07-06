/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 09:56:56 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/06 10:02:05 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_time_ms(void)
{
	struct timeval	tv;
	long			seconds;
	long			miliseconds;
	long			microseconds;

	gettimeofday(&tv, NULL);
	seconds = (long)tv.tv_sec;
	microseconds = (long)tv.tv_usec;
	miliseconds = seconds * 1000 + microseconds / 1000;
	return miliseconds;
}