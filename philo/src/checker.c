/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:26:15 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/28 14:00:29 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checker(t_philo *p)
{
	pthread_mutex_lock(&(p->for_t_philo));
	if (p->is_end)
	{
		pthread_mutex_unlock(&(p->for_t_philo));
		return (1);
	}
	if (p->times_eat != -1)
	{
		if (p->fini_num == p->philo_num)
		{
			p->is_end = 1;
			printf("%d", p->fini_num);
			pthread_mutex_unlock(&(p->for_t_philo));
			return (1);
		}
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
