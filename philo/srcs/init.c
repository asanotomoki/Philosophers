/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanotomoki <asanotomoki@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 16:06:23 by asanotomoki       #+#    #+#             */
/*   Updated: 2022/11/15 18:46:30 by asanotomoki      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_fork(t_ph *ph)
{
	int		i;

	ph->fork = malloc(sizeof(pthread_mutex_t) * ph->ph);
	if (!ph->fork)
		return (err_msg("fork malloc error"));
	i = -1;
	while (++i < ph->ph)
		pthread_mutex_init(&(ph->fork[i]), NULL);
	return (0);
}

void	man_set_data(t_ph *ph, t_man *man, int i)
{
	man->ph = ph->ph;
	man->t_die = ph->t_die;
	man->t_eat = ph->t_eat;
	man->t_sleep = ph->t_sleep;
	man->is_must_eat = ph->is_must_eat;
	if (ph->is_must_eat)
		man->must_eat = ph->must_eat;
	man->right = &ph->fork[i];
	if (i == ph->ph - 1)
		man->left = &ph->fork[0];
	else
		man->left = &ph->fork[i + 1];
	man->eat_cnt = 0;
	man->last_eat = 0;
	man->must_eat_ph = &(ph->must_eat_ph);
	man->died = &(ph->died);
	man->is_finish = &(ph->is_finish);
}

int	init_man(t_ph *ph)
{
	int		i;

	ph->man = malloc(sizeof(t_man) * ph->ph);
	if (!ph->man)
		return (err_msg("man malloc error"));
	i = -1;
	while (++i < ph->ph)
	{
		ph->man[i].position = i;
		man_set_data(ph, &(ph->man[i]), i);
	}
	return (0);
}

int	init(t_ph *ph)
{
	if (init_fork(ph))
		return (1);
	if (init_man(ph))
	{
		all_free(ph);
		return (1);
	}
	return (0);
}
