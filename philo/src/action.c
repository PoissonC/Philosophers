/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:23:48 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/21 20:27:54 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_philo *p, int idx)
{
	if (p->times_eat == -1)
		p->time_eat = 0;
}

void	eat(t_philo *p, int idx)
{

}
//after eat, they sleep
void	sleep(t_philo *p, int idx)
{

}

void	get_fork(t_philo *p, int idx)
{

}
