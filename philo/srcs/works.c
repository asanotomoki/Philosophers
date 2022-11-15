/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   works.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanotomoki <asanotomoki@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 03:16:10 by asanotomoki       #+#    #+#             */
/*   Updated: 2022/11/15 22:33:57 by asanotomoki      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "msg.h"

static void	release_fork(t_man *man)
{
	pthread_mutex_unlock(man->right);
	pthread_mutex_unlock(man->left);
}

static int	ph_eat(t_man *man)
{
	put_msg(man, EAT, YELLOW);
	pthread_mutex_lock(man->died);
	man->last_eat = get_time() + man->t_die;
	if (man->is_must_eat && check_must_eat(man))
	{	
		if (check_must_eat(man))
			return (1);
	}
	pthread_mutex_unlock(man->died);
	ph_wait(man->t_eat);
	release_fork(man);
	return (check_died(man));
}

static int	take_fork(t_man *man)
{
	if (check_died(man))
		return (1);
	if (man->position % 2)
		usleep(200);
	pthread_mutex_lock(man->right);
	put_msg(man, FORK, GREEN);
	pthread_mutex_lock(man->left);
	put_msg(man, FORK, GREEN);
	if (check_died(man))
	{
		release_fork(man);
		return (1);
	}
	return (0);
}

static int	ph_sleep(t_man *man)
{
	if (check_died(man))
		return (1);
	put_msg(man, SLEEP, BLUE);
	ph_wait(man->t_sleep);
	return (check_died(man));
}

void	*routine(void *ph_man)
{
	t_man	*man;

	man = ph_man;
	pthread_mutex_lock(man->died);
	man->last_eat = get_time() + man->t_die;
	pthread_mutex_unlock(man->died);
	while (1)
	{
		if (take_fork(man) || ph_eat(man) || ph_sleep(man))
			break ;
		put_msg(man, THINK, GRAY);
	}
	return (NULL);
}
