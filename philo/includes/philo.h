/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanotomoki <asanotomoki@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:43:45 by asanotomoki       #+#    #+#             */
/*   Updated: 2022/11/15 20:47:58 by asanotomoki      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include "err.h"

typedef struct s_man
{
	ssize_t			ph;
	ssize_t			t_die;
	ssize_t			t_eat;
	ssize_t			t_sleep;
	ssize_t			must_eat;
	bool			is_must_eat;
	bool			*is_finish;
	int				position;
	pthread_mutex_t	*right;
	pthread_mutex_t	*left;
	pthread_mutex_t	*died;
	pthread_t		th;
	int				eat_cnt;
	ssize_t			*must_eat_ph;
	ssize_t			last_eat;
}	t_man;

typedef struct s_ph
{
	ssize_t			ph;
	ssize_t			t_die;
	ssize_t			t_eat;
	ssize_t			t_sleep;
	ssize_t			must_eat;
	bool			is_must_eat;
	bool			is_finish;
	pthread_mutex_t	died;
	pthread_mutex_t	*fork;
	ssize_t			must_eat_ph;
	t_man			*man;
	pthread_t		monitor;
}	t_ph;

// util
ssize_t	ph_atol(const char *str);
ssize_t	get_time(void);
int		err_msg(char *msg);
int		all_free(t_ph *ph);

//work util
int		check_died(t_man *man);
int		check_must_eat(t_man *man);
void	ph_wait(int wait_time);
int		put_msg(t_man *man, char *msg, int color);
int		ph_solo(t_man *man);

int		init(t_ph *ph);

void	*routine(void *ph_man);

void	*monitor(void *p_data);

#endif
