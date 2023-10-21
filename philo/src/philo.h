/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychen2 <ychen2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:14:06 by ychen2            #+#    #+#             */
/*   Updated: 2023/10/21 20:39:43 by ychen2           ###   ########.fr       */
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
	int				last_eat;
	pthread_t		thr;
	pthread_mutex_t	act;
	int				eats_cur;
}				t_men;

typedef struct s_philo
{
	int				philo_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				times_eat;
	int				times_eat_cur;
	struct timeval	start_tv;
	pthread_mutex_t	*fork;
	pthread_mutex_t	get_idx;
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
int		create_philos(t_philo *p);

//utils.c
int		get_time(t_philo *p);
void	*act(t_philo *p);
void	*end_program(t_philo *p);

//destroy.c
void	destroy_forks(t_philo *p, int nums);
void	destroy_men(t_philo *p, int nums);
void	detach_philos(t_philo *p, int nums);

//main.c
void	*philos(t_philo *p);

//action.c
void	die(t_philo *p, int idx);
void	eat(t_philo *p, int idx);
void	sleep(t_philo *p, int idx);
void	think(t_philo *p, int idx);
void	get_fork(t_philo *p, int idx);
#endif