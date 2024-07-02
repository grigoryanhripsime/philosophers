/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:37:08 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/07/02 15:40:46 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_philosophers	*init(int argc, char *argv[])
{
	t_philosophers	*philos;

	philos = malloc(sizeof(t_philosophers));
	if (!philos)
		return (0);
	philos -> start = get_time();
	philos -> number_of_philos = check_num(argv[1]);
	philos -> time_to_die = check_num(argv[2]);
	philos -> time_to_eat = check_num(argv[3]);
	philos -> time_to_sleep = check_num(argv[4]);
	philos -> finish = 0;
	if (argc == 6)
		philos -> number_philos_must_eat = check_num(argv[5]);
	else
		philos -> number_philos_must_eat = -1;
	if (philos -> number_philos_must_eat == 0)
		return (0);
	if (philos -> number_of_philos == 0 || philos -> time_to_die == 0
		|| philos -> time_to_eat == 0 || philos -> time_to_sleep == 0)
		return (0);
	return (philos);
}

void	create_philos(t_philosophers *philos)
{
	int	i;

	philos -> philos = malloc(philos -> number_of_philos * sizeof(t_philo));
	if (!philos -> philos)
		return ;
	i = 0;
	while (i < philos -> number_of_philos)
	{
		philos->philos[i].index = i;
		philos->philos[i].data = philos;
		philos->philos[i].after_last_meal = philos -> start;
		philos->philos[i].number_of_times_he_ate = 0;
		philos->philos[i].pid = fork();
		if (philos->philos[i].pid == 0)
			routine(&(philos->philos[i]));
		i++;
	}
}

void	semaphores(t_philosophers *philos)
{
	philos->forks = sem_open("/forks", O_CREAT, 0644, philos->number_of_philos);
	philos->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	philos->after_last_meal_sem = sem_open("/last_meal", O_CREAT, 0644, 1);
	philos->number_of_times_he_ate_sem = sem_open("/num_he_ate",
			O_CREAT, 0644, 1);
	if (philos->forks == SEM_FAILED || philos->print_sem == SEM_FAILED)
	{
		free(philos);
		exit(printf("Sem_open failed\n"));
	}
}
