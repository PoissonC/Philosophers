/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:34:12 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/21 20:22:34 by ychen2           ###   ########.fr       */
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
	//每一毫秒檢查一次是否結束程式，可呼叫其他thread
	destroy_forks(&p, p.philo_num);
	destroy_men(&p, p.philo_num);
	return (0);
}

void	*philos(t_philo *p)
{
	static int	i;
	int			idx;

	pthread_mutex_lock(&(p->get_idx));
	idx = i++;
	pthread_mutex_unlock(&(p->get_idx));
	p->philos[idx].last_eat = get_time(p);
	while (1)
	{
		if (get_time(p) - p->philos[idx].last_eat > p->time_die)
		{
			die(p, idx);
			return (NULL);
		}
		usleep(1000);
	}
}
