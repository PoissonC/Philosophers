/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:34:12 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/22 20:37:43 by ychen2           ###   ########.fr       */
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
	destroy_forks(&p, p.philo_num);
	destroy_men(&p, p.philo_num);
	return (0);
}

void	*philos(void *philo)
{
	static int	i;
	int			idx;
	pthread_t	thr;
	t_philo		*p;

	p = philo;
	pthread_mutex_lock(&(p->for_t_philo));
	idx = i++;
	pthread_mutex_unlock(&(p->for_t_philo));
	p->philos[idx].last_eat = get_time(p);
	if (pthread_create(&thr, NULL, checker, p) != 0)
	{
		pthread_mutex_lock(&(p->for_t_philo));
		p->is_end = 1;
		pthread_mutex_unlock(&(p->for_t_philo));
	}
	if (idx & 1)
		usleep(p->time_eat * 900);
	eat(p, idx);
	pthread_join(thr, NULL);
	pthread_mutex_destroy(&(p->philos->acting));
	return (NULL);
}
