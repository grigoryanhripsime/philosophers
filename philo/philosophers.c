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
    ft_usleep(500);

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

