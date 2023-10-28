/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 18:49:40 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/28 17:20:29 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_to_die(t_philo *p)
{
	printf("%d %d died\n", p->time_die, 0);
	pthread_mutex_lock(&(p->check));
	p->is_end = 1;
	pthread_mutex_unlock(&(p->check));
}

int	get_fork_edge(t_philo *p, int idx)
{
	pthread_mutex_lock(p->fork);
	if (checker(p))
	{
		pthread_mutex_unlock(p->fork);
		return (1);
	}
	printf("%d %d has taken a fork\n", get_time(p), idx);
	if (p->philo_num == 1)
	{
		wait_to_die(p);
		return (1);
	}
	pthread_mutex_lock(p->fork + idx);
	if (checker(p))
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
	if (checker(p))
	{
		pthread_mutex_unlock(p->fork + idx);
		return (1);
	}
	printf("%d %d has taken a fork\n", get_time(p), idx);
	pthread_mutex_lock(p->fork + idx + 1);
	if (checker(p))
	{
		pthread_mutex_unlock(p->fork + idx);
		pthread_mutex_unlock(p->fork + idx + 1);
		return (1);
	}
	printf("%d %d has taken a fork\n", get_time(p), idx);
	return (0);
}

void	msleep(t_philo *p, int m_s)
{
	int	start;

	start = get_time(p);
	while ((get_time(p) - start) < m_s)
	{
		checker(p);
		usleep(100);
	}
}

int	get_time(t_philo *p)
{
	struct timeval	tv;
	int				t;

	gettimeofday(&tv, 0);
	t = (tv.tv_sec - p->start_tv.tv_sec) * 1000 + \
	(tv.tv_usec - p->start_tv.tv_usec) / 1000;
	if (t < 0)
	{
		gettimeofday(&(p->start_tv), 0);
		return (0);
	}
	else
		return (t);
}
