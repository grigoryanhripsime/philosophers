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
    philos->all_philos_finished = 0;
    philos -> dead_philo = 0;
    if (argc == 6)
	{
		philos -> number_of_times_each_philosopher_must_eat = check_num(argv[5]);
		if (philos -> number_of_times_each_philosopher_must_eat == 0)
			return (0);	
	}
    else 
        philos -> number_of_times_each_philosopher_must_eat = -1;
    if (philos -> number_of_philosophers == 0 || philos -> time_to_die == 0 || philos -> time_to_eat == 0 || philos -> time_to_sleep == 0)
        return (0);
    mutex_inits(philos);
    create_threads(philos);
    return (philos);
}

void create_threads(t_philosophers *philosophers)
{
    int i;
    philosophers -> philos = malloc(philosophers -> number_of_philosophers * sizeof(t_philo));
    if (!philosophers -> philos)
        return ;
    i = 0;
    while (i < philosophers -> number_of_philosophers)
    {
        philosophers->philos[i].index = i;
        philosophers->philos[i].data = philosophers;
        philosophers->philos[i].after_last_meal = philosophers -> start;
        philosophers->philos[i].number_of_times_he_ate = 0;
        pthread_create(&(philosophers->philos[i].thread_id), NULL, routine, &(philosophers->philos[i]));
        i++;
    }
    i = 0;
    while (i < (philosophers -> number_of_philosophers))
    {
        pthread_mutex_init(&(philosophers->philos[i].after_last_meal_mutex), NULL);
        pthread_mutex_init(&(philosophers->philos[i].number_of_times_he_ate_mutex), NULL);
        i++;
    }
}

void mutex_inits(t_philosophers *philos)
{
    pthread_mutex_init(&(philos -> dead_philo_mutex), NULL);
    pthread_mutex_init(&(philos -> print_mutex), NULL);
    pthread_mutex_init(&(philos -> all_philos_finished_mutex), NULL);
    int i;
    philos -> forks = malloc(philos->number_of_philosophers * sizeof(pthread_mutex_t));
    if (!philos -> forks)
        return ;
    i = 0;
    while (i < (philos -> number_of_philosophers))
    {
        pthread_mutex_init(&(philos->forks[i]), NULL);
        i++;
    }
}

void *routine(void *philo_void)
{
    t_philo *philo;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;

    philo = philo_void;
    if ((philo -> index + 1) % 2 == 0)
        ft_usleep(10);
    if (philo->index == 0)
        left_fork = &(philo->data->forks[philo->data->number_of_philosophers - 1]);
    else
        left_fork = &(philo->data->forks[philo->index - 1]);
    right_fork = &(philo->data->forks[philo->index]);
    while (1)
    {
        if (!eating(philo, left_fork, right_fork))
            return (0);
        if (!print(philo->data, philo->index, "is sleeping"))
            return (0);
        ft_usleep(philo->data->time_to_sleep);
        if (!print(philo->data, philo->index, "is thinking"))
            return (0);
    }
    return (0);
}

int eating(t_philo *philo, pthread_mutex_t *left_fork, pthread_mutex_t *right_fork)
{
	if (!taking_forks(philo, &left_fork, &right_fork))
		return (0);
    if (!print(philo->data, philo->index, "is eating"))
	{
		pthread_mutex_unlock(right_fork);
    	pthread_mutex_unlock(left_fork);
		return (0);
	}
    ft_usleep(philo->data->time_to_eat);
    pthread_mutex_unlock(right_fork);
    pthread_mutex_unlock(left_fork);
    pthread_mutex_lock(&(philo->after_last_meal_mutex));
    philo->after_last_meal = get_time();
    pthread_mutex_unlock(&(philo->after_last_meal_mutex));   
    pthread_mutex_lock(&(philo->number_of_times_he_ate_mutex));
    philo->number_of_times_he_ate++;
    pthread_mutex_unlock(&(philo->number_of_times_he_ate_mutex));  
    return (1);
}

int print(t_philosophers *philosophers, int index, char *message)
{
    int dead;
    int ate;

    pthread_mutex_lock(&(philosophers->dead_philo_mutex));
    dead = philosophers->dead_philo;
    pthread_mutex_unlock(&(philosophers->dead_philo_mutex));
    pthread_mutex_lock(&(philosophers->all_philos_finished_mutex));
    ate = philosophers->all_philos_finished;
    pthread_mutex_unlock(&(philosophers->all_philos_finished_mutex));
    if (dead || ate)
        return (0);
    pthread_mutex_lock(&(philosophers->print_mutex));
    printf("%ld %d %s\n", get_time() - philosophers->start, index + 1, message);
    pthread_mutex_unlock(&(philosophers->print_mutex));
    return (1);
}


int taking_forks(t_philo *philo, pthread_mutex_t **left_fork, pthread_mutex_t **right_fork)
{
    pthread_mutex_lock(*right_fork);
    if (!print(philo->data, philo->index, "has taken a fork") || philo->data->number_of_philosophers == 1)
	{
		pthread_mutex_unlock(*right_fork);
		return (0);
	}
    pthread_mutex_lock(*left_fork);
    if (!print(philo->data, philo->index, "has taken a fork") || philo->data->number_of_philosophers == 1)
	{
		pthread_mutex_unlock(*right_fork);
    	pthread_mutex_unlock(*left_fork);
		return (0);
	}
	return (1);
}