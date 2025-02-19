/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:37:28 by hrigrigo          #+#    #+#             */
/*   Updated: 2025/02/17 19:35:35 by hrigrigo         ###   ########.fr       */
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
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start;
	int				number_philos_must_eat;
	t_philo			*philos;
	sem_t			*forks;
	int				finish;
	sem_t			*finish_sem;
	sem_t			*print_sem;
	sem_t			*after_last_meal_sem;
	sem_t			*number_of_times_he_ate_sem;

}	t_philosophers;

//utils.c
int				ft_strlen(char *s);
int				check_num(char *str);
long long		get_time(void);
void			*check(void *philo_void);
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