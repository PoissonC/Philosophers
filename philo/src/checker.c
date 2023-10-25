/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:26:15 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/25 13:56:15 by yu               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_end(t_philo *p)
{
	if (p->is_end)
		return (1);
	return (0);
}

static int	is_end(t_philo *p)
{
	int	i;

	i = 0;
	while (i < p->philo_num)
	{
		if (p->times_eat != -1)
		{
			if (p->philos[i].eats_cur >= p->times_eat && \
			p->philos[i].check == 0)
			{
				p->philos[i].check = 1;
				p->fini_num++;
			}
			if (p->fini_num == p->philo_num)
				return (1);
		}
		i++;
	}
	return (0);
}

int	checker(t_philo *p)
{
	pthread_mutex_lock(&(p->for_t_philo));
	if (check_end(p))
	{
		pthread_mutex_unlock(&(p->for_t_philo));
		return (1);
	}
	if (is_end(p))
	{
		p->is_end = 1;
		pthread_mutex_unlock(&(p->for_t_philo));
		return (1);
	}
	if (get_time(p) > p->m[0].die_time)
	{
		printf("%d %d died\n", get_time(p), p->m[0].idx);
		p->is_end = 1;
		pthread_mutex_unlock(&(p->for_t_philo));
		return (1);
	}
	pthread_mutex_unlock(&(p->for_t_philo));
	return (0);
}
