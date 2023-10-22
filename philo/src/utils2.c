/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 18:49:40 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/22 19:25:29 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_die(t_philo *p, int idx)
{
	pthread_mutex_lock(&(p->philos[idx].acting));
	if (p->philos[idx].is_alive == 0)
	{
		pthread_mutex_unlock(&(p->philos[idx].acting));
		return (1);
	}
	pthread_mutex_unlock(&(p->philos[idx].acting));
	return (0);
}

int	get_fork_edge(t_philo *p, int idx)
{
	pthread_mutex_lock(p->fork);
	if (check_end(p) || check_die(p, idx))
	{
		pthread_mutex_unlock(p->fork);
		return (1);
	}
	printf("%d %d has taken a fork\n", get_time(p), idx);
	if (p->philo_num == 1)
	{
		wait_to_die(p, idx);
		return (1);
	}
	pthread_mutex_lock(p->fork + idx);
	if (check_end(p) || check_die(p, idx))
	{
		pthread_mutex_unlock(p->fork);
		pthread_mutex_unlock(p->fork + idx);
		return (1);
	}
	printf("%d %d has taken a fork\n", get_time(p), idx);
	return (0);
}

int	get_fork_mid(t_philo *p, int idx)
{
	pthread_mutex_lock(p->fork + idx);
	if (check_end(p) || check_die(p, idx))
	{
		pthread_mutex_unlock(p->fork + idx);
		return (1);
	}
	printf("%d %d has taken a fork\n", get_time(p), idx);
	pthread_mutex_lock(p->fork + idx + 1);
	if (check_end(p) || check_die(p, idx))
	{
		pthread_mutex_unlock(p->fork + idx);
		pthread_mutex_unlock(p->fork + idx + 1);
		return (1);
	}
	printf("%d %d has taken a fork\n", get_time(p), idx);
	return (0);
}
