#include "philosophers.h"

t_philosophers *init(int argc, char *argv[])
{
    t_philosophers *philos;

    philos = malloc(sizeof(t_philosophers));
    if (!philos)
        return (0);
    philos -> start = get_time();
    philos -> number_of_philosophers = check_num(argv[1]);
    philos -> time_to_die = check_num(argv[2]);
    philos -> time_to_eat = check_num(argv[3]);
    philos -> time_to_sleep = check_num(argv[4]);
    pthread_mutex_init(&(philos -> dead_philo_mutex), NULL);
    philos -> dead_philo = 0;
    if (argc == 6)
        philos -> number_of_times_each_philosopher_must_eat = check_num(argv[5]);
    else 
        philos -> number_of_times_each_philosopher_must_eat = -1;
    if (philos -> number_of_philosophers == 0 || philos -> time_to_die == 0 || philos -> time_to_eat == 0 || philos -> time_to_sleep == 0)
        return (0);
    create_threads(philos);
    create_forks(philos);
    return (philos);
}

void create_threads(t_philosophers *philosophers)
{
    int i;
    philosophers -> philos = malloc(philosophers -> number_of_philosophers * sizeof(t_philo));
    if (!philosophers -> philos)
        return ;
    i = 0;
    printf("%d\n", philosophers -> number_of_philosophers);
    while (i < philosophers -> number_of_philosophers)
    {
        philosophers->philos[i].index = i;
        philosophers->philos[i].data = philosophers;
        philosophers->philos[i].after_last_meal = philosophers -> start;
        pthread_create(&(philosophers->philos[i].thread_id), NULL, funkcia, &(philosophers->philos[i]));
        i++;
    }
}

void create_forks(t_philosophers *philos)
{
    int i;
    philos -> forks = malloc(philos->number_of_philosophers * sizeof(pthread_mutex_t));
    if (!philos -> forks)
        return ;
    i = 0;
    while (i < philos -> number_of_philosophers)
    {
        pthread_mutex_init(&(philos->philos[i].after_last_meal_mutex), NULL);
        pthread_mutex_init(&(philos->forks[i]), NULL);
        i++;
    }
}

void *funkcia(void *philo_void)
{
    t_philo *philo;

    philo = philo_void;
    if ((philo -> index + 1) % 2 == 0)
    {
        ft_usleep(10);
    }
    while (1)
    {
        pthread_mutex_lock(&(philo->data->forks[philo->index]));
        if (!print(philo->data, philo->index, "has taken a fork"))
            return (0);
        if (philo->index == 0)
            pthread_mutex_lock(&philo->data->forks[philo->data->number_of_philosophers - 1]);
        else
            pthread_mutex_lock(&philo->data->forks[philo->index - 1]);
        if (!print(philo->data, philo->index, "has taken a fork"))
            return (0);
        if (!print(philo->data, philo->index, "is eating"))
            return (0);
        ft_usleep(philo->data->time_to_eat);
        pthread_mutex_lock(&(philo->data->philos[philo->index].after_last_meal_mutex));
        philo->data->philos[philo->index].after_last_meal = get_time();
        pthread_mutex_unlock(&(philo->data->philos[philo->index].after_last_meal_mutex));
        pthread_mutex_unlock(&philo->data->forks[philo->index]);
        if (philo->index == 0)
            pthread_mutex_unlock(&philo->data->forks[philo->data->number_of_philosophers - 1]);
        else
            pthread_mutex_unlock(&philo->data->forks[philo->index - 1]);        
        if (!print(philo->data, philo->index, "is sleeping"))
            return (0);
        ft_usleep(philo->data->time_to_sleep);
        if (!print(philo->data, philo->index, "is thinking"))
            return (0);
    }
    return (0);
}

int print(t_philosophers *philosophers, int index, char *message)
{
    int dead;
    pthread_mutex_lock(&(philosophers->dead_philo_mutex));
    dead = philosophers->dead_philo;
    pthread_mutex_unlock(&(philosophers->dead_philo_mutex));
    if (dead)
        return (0);
    printf("%ld %d %s\n", get_time() - philosophers->start, index + 1, message);
    return (1);
}
