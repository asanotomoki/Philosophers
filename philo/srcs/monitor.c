/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanotomoki <asanotomoki@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:08:38 by asanotomoki       #+#    #+#             */
/*   Updated: 2022/11/15 20:46:44 by asanotomoki      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "msg.h"

static int	check_finish(t_ph *ph, t_man *man, ssize_t time)
{
	if (time >= man->last_eat)
	{
		if (!ph->is_finish)
			printf("\x1b[%dm%zu %d %s\n", RED, time, man->position + 1, DIE);
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
