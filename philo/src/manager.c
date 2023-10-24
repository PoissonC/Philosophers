/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:02:46 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/24 20:36:46 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_forks(t_philo *p, int nums)
{
	int	i;

	i = 0;
	while (i < nums)
	{
		pthread_mutex_destroy(p->fork + i);
		i++;
	}
	free(p->fork);
}

void	destroy_all(t_philo *p)
{
	destroy_forks(p, p->philo_num);
	if (p->last_eat)
	{
		free(p->last_eat);
		p->last_eat = NULL;
	}
	if (p->idx)
	{
		free(p->idx);
		p->idx = NULL;
	}
	if (p->map)
	{
		free(p->map);
		p->map = NULL;
	}
	if (p->philos)
	{
		free(p->philos);
		p->philos = NULL;
	}
}

static void	handle()
{
	
}

void	die_manage(t_philo *p, int idx)
{
	int	tmp;
	int	i;

	p->last_eat[p->map[idx]] = get_time(p);
	tmp = p->map[idx];
	i = idx;
	while (i < p->philo_num - 1)
	{
		p->map[p->idx[i]] = p->map[p->idx[i + 1]];
		i++;
	}
	p->map[i] = tmp;
	printf("map:\n");
	for (int i= 0; i< p->philo_num ; i++)
		printf("%d ",p->map[i]);
	printf("\n");
	tmp = p->idx[p->philo_num - 1];
	i = idx + 1;
	while (i < p->philo_num)
	{
		p->idx[i] = p->idx[i - 1];
		i++;
	}
	p->idx[idx] = tmp;
	printf("idx:\n");
	for (int i= 0; i< p->philo_num ; i++)
		printf("%d ",p->idx[i]);
	printf("\n");
}
