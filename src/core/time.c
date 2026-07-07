/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdomansk <mdomansk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 09:56:56 by mdomansk          #+#    #+#             */
/*   Updated: 2026/07/06 11:46:21 by mdomansk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	time_get_ms(void)
{
	struct timeval	tv;
	long			seconds;
	long			milliseconds;
	long			microseconds;

	gettimeofday(&tv, NULL);
	seconds = (long)tv.tv_sec;
	microseconds = (long)tv.tv_usec;
	miliseconds = seconds * 1000 + microseconds / 1000;
	return milliseconds;
}