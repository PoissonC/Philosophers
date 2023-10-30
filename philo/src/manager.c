/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:02:46 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/30 14:56:41 by ychen2           ###   ########.fr       */
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
	pthread_mutex_destroy(&(p->move));
	pthread_mutex_destroy(&(p->time));
	pthread_mutex_destroy(&(p->check));
	if (p->m)
	{
		free(p->m);
		p->m = NULL;
	}
	if (p->philos)
	{
		free(p->philos);
		p->philos = NULL;
	}
}

void	push_back(t_philo *p, int idx)
{
	t_manage	tmp;
	int			i;

	i = 0;
	while (i < p->philo_num)
	{
		if (idx == p->m[i].idx)
			break ;
		i++;
	}
	p->m[i].die_time = get_time(p) + p->time_die;
	tmp.idx = p->m[i].idx;
	tmp.die_time = p->m[i].die_time;
	while (i < p->philo_num - 1)
	{
		p->m[i].idx = p->m[i + 1].idx;
		p->m[i].die_time = p->m[i + 1].die_time;
		i++;
	}
	p->m[i].idx = tmp.idx;
	p->m[i].die_time = tmp.die_time;
}
