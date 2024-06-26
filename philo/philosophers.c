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
            //pthread_mutex_lock(&(philos->print_mutex));
            pthread_mutex_lock(&(philos->philos[i].after_last_meal_mutex));
            if ((get_time() - philos->philos[i].after_last_meal) >= philos->time_to_die)
            {
                pthread_mutex_unlock(&(philos->philos[i].after_last_meal_mutex));
                printf("%ld %d died\n", get_time() - philos->start, i+1);
                pthread_mutex_lock(&(philos->dead_philo_mutex));
                philos->dead_philo = 1;
                pthread_mutex_unlock(&(philos->dead_philo_mutex));
                return (0);
            }
            pthread_mutex_unlock(&(philos->philos[i].after_last_meal_mutex));

            if (philos->number_of_times_each_philosopher_must_eat < 0 || philos->philos[i].number_of_times_he_ate < philos->number_of_times_each_philosopher_must_eat)
                continue;
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
            //pthread_mutex_unlock(&(philos->print_mutex));
            i++;
        }
    }

    i = 0;
    while (i < philos -> number_of_philosophers - 1)
    {
        pthread_join(philos->philos[i].thread_id, NULL);
        pthread_mutex_destroy(&(philos -> forks[i]));
        i++;
    }
    free(philos->philos);
    free(philos->forks);
    free(philos);
}

