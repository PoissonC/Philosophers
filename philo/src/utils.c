/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:26:15 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/22 20:49:50 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	is_end(t_philo *p, int i)
{
	pthread_mutex_lock(&(p->for_t_philo));
	if (p->is_end)
	{
		pthread_mutex_unlock(&(p->for_t_philo));
		return (1);
	}
	if (p->times_eat != -1)
	{
		pthread_mutex_lock(&(p->philos[i].acting));
		if (p->philos[i].eats_cur >= p->times_eat && \
		p->philos[i].check == 0)
		{
			p->philos[i].check = 1;
			p->fini_num++;
		}
		pthread_mutex_unlock(&(p->philos[i].acting));
		if (p->fini_num == p->philo_num)
		{
			pthread_mutex_unlock(&(p->for_t_philo));
			return (1);
		}
		pthread_mutex_unlock(&(p->for_t_philo));
	}
	else
		pthread_mutex_unlock(&(p->for_t_philo));
	return (0);
}

void	*checker(void *philo)
{
	int		i;
	t_philo	*p;

	p = philo;
	while (1)
	{
		i = 0;
		while (i < p->philo_num)
		{
			if (is_end(p, i))
			{
				pthread_mutex_lock(&(p->for_t_philo));
				p->is_end = 1;
				pthread_mutex_unlock(&(p->for_t_philo));
				return (NULL);
			}
			pthread_mutex_lock(&(p->philos[i].acting));
			if (get_time(p) - p->philos[i].last_eat > p->time_die)
			{
				pthread_mutex_unlock(&(p->philos[i].acting));
				die(p, i);
			}
			else
				pthread_mutex_unlock(&(p->philos[i].acting));
			i++;
		}
		usleep(1000);
	}
}

int	check_end(t_philo *p)
{
	pthread_mutex_lock(&(p->for_t_philo));
	if (p->is_end)
	{
		pthread_mutex_unlock(&(p->for_t_philo));
		return (1);
	}
	pthread_mutex_unlock(&(p->for_t_philo));
	return (0);
}

void	wait_to_die(t_philo *p, int idx)
{
	while (1)
	{
		pthread_mutex_lock(&(p->philos[idx].acting));
		if (p->philos[idx].is_alive == 0)
			return ;
		pthread_mutex_unlock(&(p->philos[idx].acting));
		usleep(1000);
	}
}
