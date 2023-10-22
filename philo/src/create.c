/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:32:46 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/22 15:44:36 by ychen2           ###   ########.fr       */
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
	int	i;

	p->philos = malloc(sizeof(t_men) * p->philo_num);
	if (!p->philos)
	{
		destroy_forks(p, p->philo_num);
		return (1);
	}
	i = 0;
	while (i < p->philo_num)
	{
		p->philos[i].eats_cur = 0;
		p->philos[i].is_alive = 1;
		p->philos[i].check = 0;
		if (pthread_mutex_init(p->fork + i, NULL) != 0)
		{
			destroy_forks(p, p->philo_num);
			destroy_men(p, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	start_philos(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->philo_num)
	{
		if (pthread_create(&(p->philos[i].thr), NULL, philos, p) != 0)
		{
			destroy_men(p, p->philo_num);
			destroy_forks(p, p->philo_num);
			return (1);
		}
		i++;
	}
	return (0);
}
