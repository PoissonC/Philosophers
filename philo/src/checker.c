/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:26:15 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/24 19:56:55 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_end(t_philo *p)
{
	pthread_mutex_lock(&(p->for_t_philo));
	p->is_end = 1;
	pthread_mutex_unlock(&(p->for_t_philo));
}

static int	check_end(t_philo *p)
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

static int	is_end(t_philo *p, int idx)
{
	pthread_mutex_lock(&(p->for_t_philo));
	if (p->times_eat != -1)
	{
		if (p->philos[idx].eats_cur >= p->times_eat && \
		p->philos[idx].check == 0)
		{
			p->philos[idx].check = 1;
			p->fini_num++;
		}
		if (p->fini_num == p->philo_num)
		{
			pthread_mutex_unlock(&(p->for_t_philo));
			return (1);
		}
	}
	pthread_mutex_unlock(&(p->for_t_philo));
	return (0);
}

int	checker(t_philo *p, int idx)
{
	if (check_end(p))
		return (1);
	else if (is_end(p, idx))
	{
		set_end(p);
		return (1);
	}
	pthread_mutex_lock(&(p->for_t_philo));
	if (get_time(p) - p->last_eat[p->map[0]] > p->time_die)
	{
		die(p, p->map[0]);
		return (1);
	}
	pthread_mutex_unlock(&(p->for_t_philo));
	return (0);
}
