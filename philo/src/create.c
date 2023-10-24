/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:32:46 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/24 19:52:58 by ychen2           ###   ########.fr       */
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
	p->last_eat = malloc(sizeof(int) * p->philo_num);
	p->idx = malloc(sizeof(int) * p->philo_num);
	p->map = malloc(sizeof(int) * p->philo_num);
	if (!p->map || !p->idx || !p->last_eat || !p->philos)
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
	while (i < p->philo_num)
	{
		p->idx[i] = i;
		p->map[i] = i;
		p->last_eat[i] = get_time(p);
		p->philos[i].eats_cur = 0;
		p->philos[i].check = 0;
		if (pthread_create(&(p->philos[i].thr), NULL, philos, p) != 0)
		{
			set_end(p);
			destroy_all(p);
			return (1);
		}
		i++;
	}
	return (0);
}
