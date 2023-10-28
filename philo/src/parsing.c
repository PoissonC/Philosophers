/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:36:12 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/27 16:20:18 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	skipzero(char **input, int i)
{
	size_t	len;
	size_t	j;

	len = ft_strlen(input[i]);
	j = 0;
	if (input[i][0] == '+')
		j++;
	while (j < len && input[i][j] == '0')
	{
		j++;
	}
	return (len - j);
}

static int	isover(char **input, int len)
{
	int	i;
	int	num_digit;

	i = -1;
	while (++i < len)
	{
		num_digit = skipzero(input, i);
		if (num_digit > 6)
			return (1);
	}
	return (0);
}

static int	ckdigit(char **input, int len)
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

static void	init(t_philo *p, char **input)
{
	p->fini_num = 0;
	p->is_end = 0;
	p->m = NULL;
	p->philos = NULL;
	p->philo_num = ft_atoi(input[0]);
	p->time_die = ft_atoi(input[1]);
	p->time_eat = ft_atoi(input[2]);
	p->time_sleep = ft_atoi(input[3]);
}

int	parsing(t_philo *p, char **input, int argc)
{
	if (ckdigit(input + 1, argc - 1))
		return (1);
	if (isover(input + 1, argc - 1))
		return (1);
	init(p, input + 1);
	if (argc == 6)
		p->times_eat = ft_atoi(input[5]);
	else if (argc == 5)
		p->times_eat = -1;
	gettimeofday(&(p->start_tv), NULL);
	if (pthread_mutex_init(&(p->for_t_philo), NULL) != 0)
		return (1);
	if (create_forks(p))
		return (1);
	if (create_men(p))
		return (1);
	if (start_philos(p))
		return (1);
	return (0);
}
