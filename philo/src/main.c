/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:34:12 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/28 14:14:44 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	p;
	int		i;

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

void	*philos(void *philo)
{
	static int	i;
	int			idx;
	t_philo		*p;

	p = philo;
	pthread_mutex_lock(&(p->for_t_philo));
	idx = i++;
	pthread_mutex_unlock(&(p->for_t_philo));
	if (idx & 1)
		usleep(p->time_eat * 500);
	while (1)
	{
		if (eat(p, idx))
			return (NULL);
		if (p->philos[idx].eats_cur >= p->times_eat && !p->philos[idx].check)
		{
			pthread_mutex_lock(&(p->for_t_philo));
			p->fini_num++;
			pthread_mutex_unlock(&(p->for_t_philo));
			p->philos[idx].check = 1;
		}
		if (sleep_think(p, idx))
			return (NULL);
	}
}
