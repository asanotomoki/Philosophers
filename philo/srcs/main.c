/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanotomoki <asanotomoki@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 09:38:09 by asanotomoki       #+#    #+#             */
/*   Updated: 2022/11/17 14:41:36 by asanotomoki      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_mutex_destroy(t_ph *ph)
{
	int	i;

	i = -1;
	while (++i < ph->ph)
		pthread_mutex_destroy(&(ph->fork[i]));
	pthread_mutex_destroy(&(ph->died));
	return (0);
}

static int	start(t_ph *ph)
{
	int	i;

	if (ph->ph == 1)
		return (ph_solo(&ph->man[0]));
	i = -1;
	while (++i < ph->ph)
	{
		if (pthread_create(&(ph->man[i].th), NULL, \
			&routine, (void *)&(ph->man[i])))
			return (err_msg(PTHREAD_CREATE));
	}
	if (pthread_create(&(ph->monitor), NULL, &monitor, (void *)(ph)))
		return (err_msg(PTHREAD_CREATE));
	i = -1;
	while (++i < ph->ph)
	{
		if (pthread_join(ph->man[i].th, NULL))
			return (err_msg(PTHREAD_JOIN));
	}
	if (pthread_join(ph->monitor, NULL))
		return (err_msg(PTHREAD_JOIN));
	return (0);
}

static int	check_data(t_ph *ph)
{
	if (ph->ph <= 0 || ph->ph > 200)
		return (err_msg(ARG_PH));
	if (ph->t_die < 60)
		return (err_msg(ARG_DIE));
	if (ph->t_eat < 60)
		return (err_msg(ARG_EAT));
	if (ph->t_sleep < 60)
		return (err_msg(ARG_SLEEP));
	if (ph->is_must_eat && ph->must_eat <= 0)
		return (err_msg(ARG_MUST));
	return (0);
}

static int	set_data(int argc, char **argv, t_ph *ph)
{
	ph->ph = ph_atol(argv[1]);
	ph->t_die = ph_atol(argv[2]);
	ph->t_eat = ph_atol(argv[3]);
	ph->t_sleep = ph_atol(argv[4]);
	ph->must_eat_ph = 0;
	ph->is_finish = false;
	ph->is_must_eat = false;
	if (argc == 6)
	{
		ph->must_eat = ph_atol(argv[5]);
		ph->is_must_eat = true;
	}
	else
		ph->must_eat = 0;
	pthread_mutex_init(&(ph->died), NULL);
	return (check_data(ph));
}

int	main(int argc, char **argv)
{
	t_ph	ph;

	if (argc != 5 && argc != 6)
		return (err_msg(USAGE));
	if (set_data(argc, argv, &ph))
		return (1);
	if (init(&ph))
		return (1);
	if (start(&ph))
	{
		all_free(&ph);
		return (1);
	}
	ph_mutex_destroy(&ph);
	all_free(&ph);
	return (0);
}
