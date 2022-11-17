/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanotomoki <asanotomoki@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:05:19 by asanotomoki       #+#    #+#             */
/*   Updated: 2022/11/17 14:23:14 by asanotomoki      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_H
# define ERR_H

# define USAGE			"Usage : ./philo [number_of_philosophers] [time_to_die]\
[time_to_eat] [time_to_sleep] ([number_of_times_each_philosopher_must_eat])"
# define ARG_PH			"number_of_philosophers less than 0 or more than 200"
# define ARG_DIE		"time_to_die less than 60"
# define ARG_EAT		"time_to_eat less than 60"
# define ARG_SLEEP		"time_to_sleep less than 60"
# define ARG_MUST		"number_of_times_each_philosopher_must_eat less than 0"
# define PTHREAD_CREATE	"Don't create pthread"
# define PTHREAD_JOIN	"Don't join pthread"
# define MUTEX_INIT		"mutex init error"
# define PTHREAD_JOIN	"Don't join pthread"
# define PTHREAD_JOIN	"Don't join pthread"

#endif