/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:37:31 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/06/27 17:02:50 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char *argv[])
{
	t_philosophers	*philos;

	if (argc != 5 && argc != 6)
		return (printf("Error!!\nInvalid number of arguments.\n"));
	philos = init(argc, argv);
	if (!philos)
		return (printf("Invalid Argument!!!\n"));
	mutex_inits(philos);
	create_threads(philos);
	loop(philos);
	close_destroy(philos);
}

void	loop(t_philosophers	*philos)
{
	int	i;

	while (1)
	{
		pthread_mutex_lock(&(philos->all_philos_finished_mutex));
		philos->all_philos_finished = 0;
		pthread_mutex_unlock(&(philos->all_philos_finished_mutex));
		i = 0;
		while (i < philos->number_of_philos)
		{
			if (!check_dead(philos, i))
				return ;
			check_eaten(philos, i);
			i++;
		}
		pthread_mutex_lock(&(philos->all_philos_finished_mutex));
		if (philos->all_philos_finished == philos->number_of_philos)
		{
			pthread_mutex_unlock(&(philos->all_philos_finished_mutex));
			break ;
		}
		pthread_mutex_unlock(&(philos->all_philos_finished_mutex));
	}
}

int	check_dead(t_philosophers *philos, int i)
{
	pthread_mutex_lock(&(philos->philos[i].after_last_meal_mutex));
	if ((get_time() - philos->philos[i].after_last_meal) >= philos->time_to_die)
	{
		pthread_mutex_unlock(&(philos->philos[i].after_last_meal_mutex));
		print(philos, i, "died");
		pthread_mutex_lock(&(philos->dead_philo_mutex));
		philos->dead_philo = 1;
		pthread_mutex_unlock(&(philos->dead_philo_mutex));
		return (0);
	}
	pthread_mutex_unlock(&(philos->philos[i].after_last_meal_mutex));
	return (1);
}

int	check_eaten(t_philosophers *philos, int i)
{
	if (philos->number_philos_must_eat < 0)
		return (1);
	pthread_mutex_lock(&(philos->philos[i].number_of_times_he_ate_mutex));
	if (philos->philos[i].number_of_times_he_ate
		>= philos->number_philos_must_eat)
	{
		pthread_mutex_unlock(&(philos->philos[i].number_of_times_he_ate_mutex));
		pthread_mutex_lock(&(philos->all_philos_finished_mutex));
		philos->all_philos_finished++;
		pthread_mutex_unlock(&(philos->all_philos_finished_mutex));
		return (0);
	}
	pthread_mutex_unlock(&(philos->philos[i].number_of_times_he_ate_mutex));
	return (1);
}

void	close_destroy(t_philosophers *philos)
{
	int	i;

	i = 0;
	while (i < philos -> number_of_philos)
	{
		pthread_join(philos->philos[i].thread_id, NULL);
		pthread_mutex_destroy(&(philos -> forks[i]));
		pthread_mutex_destroy(&(philos->philos[i].after_last_meal_mutex));
		pthread_mutex_destroy(
			&(philos->philos[i].number_of_times_he_ate_mutex));
		i++;
	}
	pthread_mutex_destroy(&(philos -> dead_philo_mutex));
	pthread_mutex_destroy(&(philos -> print_mutex));
	pthread_mutex_destroy(&(philos -> all_philos_finished_mutex));
	free(philos->philos);
	free(philos->forks);
	free(philos);
}
