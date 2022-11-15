/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanotomoki <asanotomoki@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:43:16 by asanotomoki       #+#    #+#             */
/*   Updated: 2022/11/15 22:18:17 by asanotomoki      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

ssize_t	ph_atol(const char *str)
{
	int		sign;
	ssize_t	num;

	sign = -1;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str == '+')
		sign = -(44 - *str++);
	if (*str == '-')
		return (-1);
	num = 0;
	while ('0' <= *str && *str <= '9')
		num = (num * 10) - (*str++ - '0');
	return (num * sign);
}

int	all_free(t_ph *ph)
{
	if (ph->man)
		free(ph->man);
	if (ph->fork)
		free(ph->fork);
	return (0);
}

int	err_msg(char *msg)
{
	size_t	len;

	len = 0;
	while (msg[len])
		len++;
	write(2, msg, len);
	write(2, "\n", 2);
	return (1);
}

ssize_t	get_time(void)
{
	static struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
