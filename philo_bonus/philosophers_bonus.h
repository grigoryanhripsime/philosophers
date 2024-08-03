/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:37:28 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/07/06 17:38:38 by hrigrigo         ###   ########.fr       */
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
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_philosophers	t_philosophers;

typedef struct s_philo
{
	int				index;
	int				pid;
	pthread_t		thread_id;
	size_t			after_last_meal;
	int				number_of_times_he_ate;
	t_philosophers	*data;
}	t_philo;

typedef struct s_philosophers
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	size_t			start;
	int				number_philos_must_eat;
	int				die;
	t_philo			*philos;
	sem_t			*forks;
	sem_t			*print_sem;
	sem_t			*after_last_meal_sem;
	sem_t			*number_of_times_he_ate_sem;
	sem_t			*die_sem;
}	t_philosophers;

//utils.c
int				ft_strlen(char *s);
int				check_num(char *str, int index);
long long		get_time(void);
void			ft_usleep(long long mls);

//philosophers_bonus.c
int				main(int argc, char *argv[]);
int				check_dead(t_philosophers *philos);
int				check_eaten(t_philosophers *philos);
void			close_destroy(t_philosophers *philos);

//init.c
t_philosophers	*init(int argc, char *argv[]);
void			create_philos(t_philosophers *philosophers);
void			semaphores(t_philosophers *philos);

//routine.c
void			finished(t_philo *philo);
void			routine(t_philo *philo);
int				eating(t_philo *philo);
int				print(t_philosophers *philosophers, int index,
					char *message);

#endif