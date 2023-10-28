/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:32:46 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/28 17:22:10 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_forks(t_philo *p)
{
	int	i;

	p->fork = malloc(sizeof(pthread_mutex_t) * p->philo_num);
	if (!p->fork)
		return (1);
	i = 0;
	while (i < p->philo_num)
	{
		if (pthread_mutex_init(p->fork + i, NULL) != 0)
		{
			destroy_forks(p, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_men(t_philo *p)
{
	if (pthread_mutex_init(&(p->move), NULL))
	{
		destroy_all(p);
		return (1);
	}
	if (pthread_mutex_init(&(p->check), NULL))
	{
		pthread_mutex_destroy(&(p->move));
		destroy_all(p);
		return (1);
	}
	p->philos = malloc(sizeof(t_men) * p->philo_num);
	p->m = malloc(sizeof(t_manage) * p->philo_num);
	if (!p->philos || !p->m)
	{
		destroy_all(p);
		return (1);
	}
	return (0);
}

int	start_philos(t_philo *p)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(p->move));
	while (i < p->philo_num)
	{
		p->m[i].die_time = p->time_die;
		p->m[i].idx = i;
		p->philos[i].cur = 0;
		p->philos[i].check = 0;
		if (pthread_create(&(p->philos[i].thr), NULL, philos, p) != 0)
		{
			p->is_end = 1;
			pthread_mutex_destroy(&(p->move));
			pthread_mutex_destroy(&(p->check));
			destroy_all(p);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&(p->move));
	return (0);
}
