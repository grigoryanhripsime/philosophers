/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:37:08 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/10/04 16:51:36 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		philos -> number_philos_must_eat = -2;
	if (philos -> number_philos_must_eat == -1)
		return (0);
	if (philos -> number_of_philos == -1 || philos -> time_to_die == -1
		|| philos -> time_to_eat == -1 || philos -> time_to_sleep == -1)
		return (0);
	return (philos);
}

void	create_threads(t_philosophers *philos)
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
		pthread_create(&(philos->philos[i].thread_id), NULL,
			routine, &(philos->philos[i]));
		i++;
	}
	i = 0;
	while (i < (philos -> number_of_philos))
	{
		pthread_mutex_init(&(philos->philos[i].after_last_meal_mutex), NULL);
		pthread_mutex_init(&(philos->philos[i].number_of_times_he_ate_mutex),
			NULL);
		i++;
	}
}

void	mutex_inits(t_philosophers *philos)
{
	int	i;

	pthread_mutex_init(&(philos -> print_mutex), NULL);
	pthread_mutex_init(&(philos -> finish_mutex), NULL);
	philos -> forks = malloc(philos->number_of_philos
			* sizeof(pthread_mutex_t));
	if (!philos -> forks)
		return ;
	i = 0;
	while (i < (philos -> number_of_philos))
	{
		pthread_mutex_init(&(philos->forks[i]), NULL);
		i++;
	}
}
