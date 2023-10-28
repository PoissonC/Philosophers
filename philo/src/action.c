/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:23:48 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/28 14:05:45 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_fork(t_philo *p, int idx)
{
	if (p->philos[idx].check == 1)
		return (0);
	else if (idx == p->philo_num - 1)
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

int	eat(t_philo *p, int idx)
{
	if (p->philos[idx].check == 0)
		if (get_fork(p, idx) == 1)
			return (1);
	if (checker(p))
		return (1);
	if (p->philos[idx].check == 0)
	{
		printf("%d %d is eating\n", get_time(p), idx);
		p->philos[idx].eats_cur++;
	}
	push_back(p, idx);
	msleep(p, p->time_eat);
	put_fork(p, idx);
	return (0);
}

int	sleep_think(t_philo *p, int idx)
{
	if (checker(p))
		return (1);
	if (p->philos[idx].check == 0)
		printf("%d %d is sleeping\n", get_time(p), idx);
	msleep(p, p->time_sleep);
	if (checker(p))
		return (1);
	if (p->philos[idx].check == 0)
		printf("%d %d is thinking\n", get_time(p), idx);
	return (0);
}
