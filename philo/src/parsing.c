/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:36:12 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/21 20:03:51 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	skipzero(char **input, int i[])
{
	size_t	len;
	size_t	j;

	len = ft_strlen(input[i[0]]);
	j = 0;
	if (input[i[0]][0] == '-' || input[i[0]][0] == '+')
	{
		if (input[i[0]][0] == '-')
			i[1] = 1;
		j++;
	}
	while (j < len && input[i[0]][j] == '0')
	{
		j++;
	}
	i[2] = (int)j;
	return (len - j);
}

int	isover(char **input, int len)
{
	int		i[3];

	i[0] = -1;
	while (++i[0] < len)
	{
		i[1] = 0;
		len = skipzero(input, i);
		if (len > 11)
			return (1);
		if (len == 10 && i[1] == 1)
			if (ft_strncmp(input[i[0]] + i[2], "2147483648", 10) > 0)
				return (1);
		if (len == 10 && i[1] == 0)
			if (ft_strncmp(input[i[0]] + i[2], "2147483647", 10) > 0)
				return (1);
	}
	return (0);
}

int	ckdigit(char **input, int len)
{
	int	i;
	int	j;

	i = 0;
	while (i < len)
	{
		j = 0;
		if (input[i][j] == '+')
			j++;
		while (input[i][j] != '\0')
			if (!ft_isdigit(input[i][j++]))
				return (1);
		if (j == 1 && (input[i][0] == '+'))
			return (1);
		i++;
	}
	return (0);
}

int	parsing(t_philo *p, char **input, int argc)
{
	if (ckdigit(input + 1, argc - 1))
		return (1);
	if (isover(input + 1, argc - 1))
		return (1);
	p->philo_num = ft_atoi(input[1]);
	p->time_die = ft_atoi(input[2]);
	p->time_eat = ft_atoi(input[3]);
	p->time_sleep = ft_atoi(input[4]);
	p->times_eat_cur = 0;
	if (argc == 6)
		p->times_eat = ft_atoi(input[5]);
	else if (argc == 5)
		p->times_eat = -1;
	p->start_tv.tv_sec = 0;
	p->start_tv.tv_usec = 0;
	if (pthread_mutex_init(&(p->get_idx), NULL) != 0)
		return (1);
	if (create_forks(p))
		return (1);
	if (create_men(p))
		return (1);
	if (create_philos(p))
		return (1);
	return (0);
}
