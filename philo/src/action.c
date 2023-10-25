/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:23:48 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/25 13:19:49 by yu               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_fork(t_philo *p, int idx)
{
	if (idx == p->philo_num - 1)
	{
		if (get_fork_edge(p, idx))
			return (1);
	}
	else
	{
		if (get_fork_mid(p, idx))
			return (1);
	}
	return (0);
}

void	put_fork(t_philo *p, int idx)
{
	if (idx == p->philo_num - 1)
	{
		pthread_mutex_unlock(p->fork);
		pthread_mutex_unlock(p->fork + idx);
	}
	else
	{
		pthread_mutex_unlock(p->fork + idx);
		pthread_mutex_unlock(p->fork + idx + 1);
	}
}

void	eat(t_philo *p, int idx)
{
	if (get_fork(p, idx) == 1)
		return ;
	if (checker(p))
	{
		put_fork(p, idx);
		return ;
	}
	printf("%d %d  is eating\n", get_time(p), idx);
	pthread_mutex_lock(&(p->for_t_philo));
	p->philos[idx].eats_cur++;
	push_back(p, idx);
	pthread_mutex_unlock(&(p->for_t_philo));
	msleep(p, p->time_eat);
	put_fork(p, idx);
	sleep_think(p, idx);
}

void	sleep_think(t_philo *p, int idx)
{
	if (checker(p))
		return ;
	printf("%d %d is sleeping\n", get_time(p), idx);
	msleep(p, p->time_sleep);
	if (checker(p))
		return ;
	printf("%d %d is thinking\n", get_time(p), idx);
	eat(p, idx);
}
