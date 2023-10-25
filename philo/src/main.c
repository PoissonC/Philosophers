/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:34:12 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/25 12:31:16 by yu               ###   ########.fr       */
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
	eat(p, idx);
	return (NULL);
}
