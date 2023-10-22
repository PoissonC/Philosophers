/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:23:48 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/22 19:27:23 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_fork(t_philo *p, int idx)
{
	if (check_end(p) || check_die(p, idx))
		return (1);
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
	if (check_end(p) || check_die(p, idx))
	{
		if (get_fork(p, idx) == 0)
			put_fork(p, idx);
		return ;
	}
	pthread_mutex_lock(&(p->philos[idx].acting));
	printf("%d %d  is eating\n", get_time(p), idx);
	p->philos[idx].eats_cur++;
	p->philos[idx].last_eat = get_time(p);
	usleep(p->time_eat * 1000);
	put_fork(p, idx);
	pthread_mutex_unlock(&(p->philos[idx].acting));
	sleep_think(p, idx);
}

void	sleep_think(t_philo *p, int idx)
{
	if (check_end(p) || check_die(p, idx))
		return ;
	pthread_mutex_lock(&(p->philos[idx].acting));
	printf("%d %d is sleeping\n", get_time(p), idx);
	usleep(p->time_sleep * 1000);
	pthread_mutex_unlock(&(p->philos[idx].acting));
	if (check_end(p) || check_die(p, idx))
		return ;
	pthread_mutex_lock(&(p->philos[idx].acting));
	printf("%d %d is thinking\n", get_time(p), idx);
	usleep(p->time_sleep * 1000);
	pthread_mutex_unlock(&(p->philos[idx].acting));
	eat(p, idx);
}

void	die(t_philo *p, int idx)
{
	if (check_end(p))
		return ;
	pthread_mutex_lock(&(p->for_t_philo));
	if (p->times_eat == -1)
		p->is_end = 1;
	pthread_mutex_unlock(&(p->for_t_philo));
	pthread_mutex_lock(&(p->philos[idx].acting));
	if (p->philos[idx].is_alive == 0)
	{
		pthread_mutex_unlock(&(p->philos[idx].acting));
		return ;
	}
	printf("%d %d died\n", get_time(p), idx);
	p->philos[idx].is_alive = 0;
	pthread_mutex_unlock(&(p->philos[idx].acting));
}
