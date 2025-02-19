/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:37:28 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/06/29 13:50:48 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philosophers	t_philosophers;

typedef struct s_philo
{
	int				index;
	pthread_t		thread_id;
	size_t			after_last_meal;
	pthread_mutex_t	after_last_meal_mutex;
	int				number_of_times_he_ate;
	pthread_mutex_t	number_of_times_he_ate_mutex;
	t_philosophers	*data;
}	t_philo;

typedef struct s_philosophers
{
	int				number_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start;
	int				number_philos_must_eat;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				finish;
	pthread_mutex_t	finish_mutex;
	pthread_mutex_t	print_mutex;
}	t_philosophers;

//utils.c
int				ft_strlen(char *s);
int				check_num(char *str);
long long		get_time(void);
void			ft_usleep(long long mls);

//philosophers.c
int				main(int argc, char *argv[]);
int				check_dead(t_philosophers *philos);
int				check_eaten(t_philosophers *philos);
void			close_destroy(t_philosophers *philos);

//init.c
t_philosophers	*init(int argc, char *argv[]);
void			create_threads(t_philosophers *philosophers);
void			mutex_inits(t_philosophers *philos);

//routine.c
int				finished(t_philosophers *philos);
void			*routine(void *philo_void);
int				eating(t_philo *philo,
					pthread_mutex_t *l_fork, pthread_mutex_t *r_fork);
int				print(t_philosophers *philosophers,
					int index, char *message);
int				taking_forks(t_philo *philo,
					pthread_mutex_t **left_fork, pthread_mutex_t **right_fork);

#endif