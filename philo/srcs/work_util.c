/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanotomoki <asanotomoki@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:58:32 by asanotomoki       #+#    #+#             */
/*   Updated: 2022/11/15 20:51:49 by asanotomoki      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "msg.h"

int	ph_solo(t_man *man)
{
	printf("\x1b[%dm%zu %d %s\n", GREEN, get_time(), man->position + 1, FORK);
	ph_wait(man->t_die);
	printf("\x1b[%dm%zu %d %s\n", RED, get_time(), man->position + 1, DIE);
	return (0);
}

int	check_must_eat(t_man *man)
{
	if (++man->eat_cnt == man->must_eat)
	{
		*man->must_eat_ph += 1;
		if (*man->must_eat_ph == man->ph)
		{
			*man->is_finish = true;
			pthread_mutex_unlock(man->died);
			pthread_mutex_unlock(man->right);
			pthread_mutex_unlock(man->left);
			return (1);
		}
	}
	return (0);
}

int	put_msg(t_man *man, char *msg, int color)
{
	pthread_mutex_lock(man->died);
	if (!(*man->is_finish))
		printf("\x1b[%dm%zu %d %s\n", color, get_time(), man->position + 1, msg);
	pthread_mutex_unlock(man->died);
	return (0);
}

int	check_died(t_man *man)
{
	pthread_mutex_lock(man->died);
	if (*man->is_finish)
	{
		pthread_mutex_unlock(man->died);
		return (1);
	}
	pthread_mutex_unlock(man->died);
	return (0);
}

void	ph_wait(int wait_time)
{
	size_t	start;
	size_t	time;

	start = get_time();
	while (1)
	{
		time = get_time();
		if (time >= start + wait_time)
			return ;
		usleep(50);
	}
}
