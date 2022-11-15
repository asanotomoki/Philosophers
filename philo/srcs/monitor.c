/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanotomoki <asanotomoki@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:08:38 by asanotomoki       #+#    #+#             */
/*   Updated: 2022/11/15 22:42:01 by asanotomoki      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "msg.h"

static int	check_finish(t_ph *ph, t_man *man, ssize_t time)
{
	if (man->last_eat == 0)
		return (0);
	else if (time >= man->last_eat)
	{
		if (!ph->is_finish)
			printf("\x1b[%dm%zu %d %s\x1b[0m\n", \
			RED, time, man->position + 1, DIE);
		ph->is_finish = true;
		pthread_mutex_unlock(&ph->died);
		return (1);
	}
	return (0);
}

void	*monitor(void *p_data)
{
	t_ph	*ph;
	int		i;

	ph = p_data;
	while (1)
	{
		i = -1;
		pthread_mutex_lock(&ph->died);
		while (++i < ph->ph)
		{
			if (check_finish(ph, &ph->man[i], get_time()))
				return (NULL);
		}
		pthread_mutex_unlock(&ph->died);
		usleep(50);
	}
}
