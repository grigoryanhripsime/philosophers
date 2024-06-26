#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

typedef struct s_philosophers t_philosophers;

typedef struct s_philo 
{
    int index;
    pthread_t thread_id;
    size_t after_last_meal;
    pthread_mutex_t after_last_meal_mutex;
    int number_of_times_he_ate;
    pthread_mutex_t number_of_times_he_ate_mutex;
    t_philosophers *data;
} t_philo;

typedef struct s_philosophers 
{
    int number_of_philosophers;
    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    size_t start;
    int number_of_times_each_philosopher_must_eat;
    int all_philos_finished;
    pthread_mutex_t all_philos_finished_mutex;
    t_philo *philos;
    pthread_mutex_t *forks;
    int dead_philo;
    pthread_mutex_t dead_philo_mutex;
    pthread_mutex_t print_mutex;
} t_philosophers;


//validation.c
int	ft_isspace(char c);
int ft_strlen(char *s);
int	check_num(char *str);

//philosophers.c
int main(int argc, char *argv[]);

//init.c
t_philosophers *init(int argc, char *argv[]);
void create_threads(t_philosophers *philosophers);
void create_forks(t_philosophers *philos);
void *funkcia(void *philo_void);
int print(t_philosophers *philosophers, int index, char *message);

//time.c
size_t get_time(void);
int ft_usleep(int mls);


#endif