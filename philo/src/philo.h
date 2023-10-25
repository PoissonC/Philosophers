/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yu <yu@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:14:06 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/25 13:50:17 by yu               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "../libft/libft.h"
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>

typedef struct s_men
{
	pthread_t	thr;
	int			eats_cur;
	int			check;
}				t_men;

typedef struct s_manage
{
	int	idx;
	int	die_time;
}				t_manage;

typedef struct s_philo
{
	int				philo_num;
	int				fini_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				times_eat;
	t_manage		*m;
	int				is_end;
	struct timeval	start_tv;
	pthread_mutex_t	*fork;
	pthread_mutex_t	for_t_philo;
	t_men			*philos;
}			t_philo;

enum e_act
{
	TAKE_FORK = 1,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_act;
//parsing.c
int		parsing(t_philo *p, char **input, int argc);

//create.c
int		create_forks(t_philo *p);
int		create_men(t_philo *p);
int		start_philos(t_philo *p);

//checker.c
int		checker(t_philo *philo);
void	msleep(t_philo *p, int m_s);

//utils.c
int		get_fork_edge(t_philo *p, int idx);
int		get_fork_mid(t_philo *p, int idx);
int		get_time(t_philo *p);

//manger.c
void	destroy_forks(t_philo *p, int nums);
void	destroy_all(t_philo *p);
void	push_back(t_philo *p, int idx);

//main.c
void	*philos(void *philo);

//action.c
void	eat(t_philo *p, int idx);
void	sleep_think(t_philo *p, int idx);
int		get_fork(t_philo *p, int idx);
void	put_fork(t_philo *p, int idx);
#endif