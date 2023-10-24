/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:23:48 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/24 20:02:18 by ychen2           ###   ########.fr       */
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
	if (checker(p, idx))
	{
		put_fork(p, idx);
		return ;
	}
	printf("%d %d  is eating\n", get_time(p), idx);
	p->philos[idx].eats_cur++;
	die_manage(p, idx);
	usleep(p->time_eat * 1000);
	put_fork(p, idx);
	sleep_think(p, idx);
}

void	sleep_think(t_philo *p, int idx)
{
	if (checker(p, idx))
		return ;
	printf("%d %d is sleeping\n", get_time(p), idx);
	usleep(p->time_sleep * 1000);
	if (checker(p, idx))
		return ;
	printf("%d %d is thinking\n", get_time(p), idx);
	eat(p, idx);
}

void	die(t_philo *p, int idx)
{
	printf("%d %d died\n", get_time(p), idx);
	p->is_end = 1;
	pthread_mutex_unlock(&(p->for_t_philo));
}
