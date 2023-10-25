/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:32:46 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/25 14:14:02 by yu               ###   ########.fr       */
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
	pthread_mutex_lock(&(p->for_t_philo));
	while (i < p->philo_num)
	{
		p->m[i].die_time = p->time_die;
		p->m[i].idx = i;
		p->philos[i].eats_cur = 0;
		p->philos[i].check = 0;
		if (pthread_create(&(p->philos[i].thr), NULL, philos, p) != 0)
		{
			p->is_end = 1;
			destroy_all(p);
			return (1);
		}
		i++;
	}
	pthread_mutex_unlock(&(p->for_t_philo));
	return (0);
}
