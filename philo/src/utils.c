/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:26:15 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/21 20:38:54 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(t_philo *p)
{
	struct timeval	tv;
	int				t;

	gettimeofday(&tv, 0);
	t = (tv.tv_sec - p->start_tv.tv_sec) * 1000 + \
	(tv.tv_usec - p->start_tv.tv_usec) / 1000;
	if (t < 0)
	{
		gettimeofday(&(p->start_tv), 0);
		return (0);
	}
	else
		return (t);
}

void	*act(t_philo *p)
{

}
