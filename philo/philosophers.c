#include "philosophers.h"

int main(int argc, char *argv[])
{
    t_philosophers *philos;
    int i;

    if (argc != 5 && argc != 6)
        return (printf("Error!!\nInvalid number of arguments.\n"));
    philos = init(argc, argv);
    if (!philos)
        return (printf("Invalid Argument!!!\n"));
    while (1)
    {
        i = 0;
        while (i < philos->number_of_philosophers)
        {
            if (!check_dead(philos, i))
                return (0);
            if (!check_eaten(philos, i))
                return (0);
            i++;
        }
    }
    close_destroy(philos);
}
int check_dead(t_philosophers *philos, int i)
{
    pthread_mutex_lock(&(philos->philos[i].after_last_meal_mutex));
    if ((get_time() - philos->philos[i].after_last_meal) >= philos->time_to_die)
    {
        pthread_mutex_unlock(&(philos->philos[i].after_last_meal_mutex));
        print(philos, i, "is dead");
        pthread_mutex_lock(&(philos->dead_philo_mutex));
        philos->dead_philo = 1;
        pthread_mutex_unlock(&(philos->dead_philo_mutex));
        return (0);
    }
    pthread_mutex_unlock(&(philos->philos[i].after_last_meal_mutex));
    return (1);
}

int check_eaten(t_philosophers *philos, int i)
{
    if (philos->number_of_times_each_philosopher_must_eat < 0 || philos->philos[i].number_of_times_he_ate < philos->number_of_times_each_philosopher_must_eat)
        return (1);
    pthread_mutex_lock(&(philos->philos[i].number_of_times_he_ate_mutex));
    if (philos->philos[i].number_of_times_he_ate >= philos->number_of_times_each_philosopher_must_eat)
    {
        pthread_mutex_unlock(&(philos->philos[i].number_of_times_he_ate_mutex));

        pthread_mutex_lock(&(philos->all_philos_finished_mutex));
        philos->all_philos_finished = 1;
        pthread_mutex_unlock(&(philos->all_philos_finished_mutex));
        return (0);
    }
    pthread_mutex_unlock(&(philos->philos[i].number_of_times_he_ate_mutex));
    return (1);
}

void close_destroy(t_philosophers *philos)
{
    int i;

    i = 0;
    while (i < philos -> number_of_philosophers - 1)
    {
        pthread_join(philos->philos[i].thread_id, NULL);
        pthread_mutex_destroy(&(philos -> forks[i]));
        pthread_mutex_destroy(&(philos->philos[i].after_last_meal_mutex));
        pthread_mutex_destroy(&(philos->philos[i].number_of_times_he_ate_mutex));
        i++;
    }
    pthread_mutex_destroy(&(philos -> dead_philo_mutex));
    pthread_mutex_destroy(&(philos -> print_mutex));
    pthread_mutex_destroy(&(philos -> all_philos_finished_mutex));
    free(philos->philos);
    free(philos->forks);
    free(philos);
}
