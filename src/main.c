/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:34:12 by ychen2            #+#    #+#             */
/*   Updated: 2023/11/03 18:35:59 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo		p;
	int			i;

	if (argc != 6 && argc != 5)
		return (1);
	if (parsing(&p, argv, argc))
		return (1);
	i = 0;
	while (i < p.philo_num)
	{
		pthread_join(p.philos[i].thr, NULL);
		i++;
	}
	destroy_all(&p);
	return (0);
}

static int	get_idx(t_philo *p)
{
	static int	i;

	pthread_mutex_lock(&(p->move));
	return (i++);
}

void	*philos(void *philo)
{
	int			idx;
	t_philo		*p;

	p = philo;
	idx = get_idx(p);
	pthread_mutex_unlock(&(p->move));
	if (idx & 1)
		msleep(p, p->time_eat - 50);
	while (1)
	{
		if (eat(p, idx))
			return (NULL);
		if (p->times_eat != -1)
		{
			if (p->philos[idx].cur >= p->times_eat && !p->philos[idx].check)
			{
				pthread_mutex_lock(&(p->check));
				p->fini_num++;
				pthread_mutex_unlock(&(p->check));
				p->philos[idx].check = 1;
			}
		}
		if (sleep_think(p, idx))
			return (NULL);
	}
}
