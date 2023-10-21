/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:02:46 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/21 20:11:36 by ychen2           ###   ########.fr       */
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

void	destroy_men(t_philo *p, int nums)
{
	int	i;

	i = 0;
	while (i < nums)
	{
		pthread_mutex_destroy(&(p->philos[i].act));
		i++;
	}
	free(p->philos);
}

void	detach_philos(t_philo *p, int nums)
{
	int	i;

	i = 0;
	while (i < nums)
	{
		pthread_detach(p->philos[i].thr);
		i++;
	}
	free(p->philos);
}
