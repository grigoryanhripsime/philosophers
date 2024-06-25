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
            // printf("%ld\n", data->time_to_die);
            if ((get_time() - philos->philos[i].after_last_meal) >= philos->time_to_die)
            {
                printf("going to be dead: %ld %ld\n", philos->philos[i].after_last_meal, get_time());
                printf("%ld %d died\n", get_time() - philos->start, i);
                pthread_mutex_lock(&(philos->dead_philo_mutex));
                philos->dead_philo = 1;
                pthread_mutex_unlock(&(philos->dead_philo_mutex));
                return (0);
            }
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

