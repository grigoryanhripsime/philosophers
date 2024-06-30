/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:37:28 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/06/30 19:28:04 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <semaphore.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philosophers	t_philosophers;

typedef struct s_philo
{
	int				index;
	int				pid;
	pthread_t thread_id;
	size_t			after_last_meal;
	sem_t	after_last_meal_mutex;
	int				number_of_times_he_ate;
	sem_t	number_of_times_he_ate_mutex;
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
	sem_t	forks;
	int				finish;
	sem_t	print_mutex;
}	t_philosophers;

//utils.c
int				ft_strlen(char *s);
int				check_num(char *str);
long long		get_time(void);
void			ft_usleep(long long mls);

//philosophers_bonus.c
int				main(int argc, char *argv[]);
int				check_dead(t_philosophers *philos);
int				check_eaten(t_philosophers *philos);
void			close_destroy(t_philosophers *philos);

//init.c
t_philosophers	*init(int argc, char *argv[]);
void			create_forks(t_philosophers *philosophers);
void			mutex_inits(t_philosophers *philos);

//routine.c
int				finished(t_philosophers *philos);
void			routine(t_philo *philo);
int				eating(t_philo *philo,
					pthread_mutex_t *l_fork, pthread_mutex_t *r_fork);
int				print(t_philosophers *philosophers,
					int index, char *message);
int				taking_forks(t_philo *philo,
					pthread_mutex_t **left_fork, pthread_mutex_t **right_fork);

#endif