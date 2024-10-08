/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:14:06 by ychen2            #+#    #+#             */
/*   Updated: 2024/03/08 10:28:58 by ychen2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_men
{
	pthread_t	thr;
	int			cur;
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
	pthread_mutex_t	*fork;
	pthread_mutex_t	move;
	pthread_mutex_t	check;
	int				start_time;
	t_men			*philos;
}			t_philo;

typedef enum e_act
{
	TAKE_FORK = 1,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_act;

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
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
int		eat(t_philo *p, int idx);
int		sleep_think(t_philo *p, int idx);
#endif