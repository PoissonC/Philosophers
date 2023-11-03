/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:23:48 by ychen2            #+#    #+#             */
/*   Updated: 2023/11/03 18:36:19 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_fork(t_philo *p, int idx)
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

static void	put_fork(t_philo *p, int idx)
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

int	eat(t_philo *p, int idx)
{
	pthread_mutex_lock(&(p->move));
	if (p->philos[idx].check == 0)
	{
		if (get_fork(p, idx) == 1)
		{
			pthread_mutex_unlock(&(p->move));
			return (1);
		}
	}
	pthread_mutex_unlock(&(p->move));
	if (checker(p))
		return (1);
	if (p->philos[idx].check == 0)
	{
		printf("%d %d is eating\n", get_time(p), idx + 1);
		p->philos[idx].cur++;
	}
	pthread_mutex_lock(&(p->check));
	push_back(p, idx);
	pthread_mutex_unlock(&(p->check));
	msleep(p, p->time_eat);
	put_fork(p, idx);
	return (0);
}

int	sleep_think(t_philo *p, int idx)
{
	if (checker(p))
		return (1);
	if (p->philos[idx].check == 0)
		printf("%d %d is sleeping\n", get_time(p), idx + 1);
	msleep(p, p->time_sleep);
	if (checker(p))
		return (1);
	if (p->philos[idx].check == 0)
		printf("%d %d is thinking\n", get_time(p), idx + 1);
	return (0);
}
