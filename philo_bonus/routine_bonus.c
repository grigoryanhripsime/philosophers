/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:37:36 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/07 13:57:50 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	check_die(t_philo *philo)
{
	long long	time;

	sem_wait(philo->data->after_last_meal_sem);
	time = philo->after_last_meal;
	sem_post(philo->data->after_last_meal_sem);
	sem_post(philo->data->after_last_meal_sem);
	if (get_time() - time >= philo->data->time_to_die)
	{
		sem_wait(philo->data->die_sem);
		philo->data->die = 1;
		sem_post(philo->data->die_sem);
		sem_wait(philo->data->print_sem);
		printf("%lld %d %s", get_time(), philo->index + 1, "died\n");
		exit(1);
	}
	return (0);
}

int	check_eat(t_philo *philo)
{
	sem_wait(philo->data->number_of_times_he_ate_sem);
	if (philo->number_of_times_he_ate == philo->data->number_philos_must_eat)
	{
		sem_wait(philo->data->die_sem);
		philo->data->die = 1;
		sem_post(philo->data->die_sem);
		sem_post(philo->data->number_of_times_he_ate_sem);
		exit (0);
	}
	sem_post(philo->data->number_of_times_he_ate_sem);
	return (0);
}

void	*check(t_philo *philo)
{
	while (1)
	{
		if (check_die(philo) == 1 || check_eat(philo) == 1)
			break ;
	}
	return (NULL);
}

void	routine(t_philo *philo)
{
	pthread_create(&philo->thread_id, NULL, (void *)check, philo);
	while (1)
	{
		sem_wait(philo->data->forks);
		print(philo->data, philo->index, "has taken a fork");
		sem_wait(philo->data->forks);
		print(philo->data, philo->index, "has taken a fork");
		print(philo->data, philo->index, "is eating");
		ft_usleep(philo->data->time_to_eat);
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		sem_wait(philo->data->number_of_times_he_ate_sem);
		philo->number_of_times_he_ate++;
		sem_post(philo->data->number_of_times_he_ate_sem);
		sem_wait(philo->data->after_last_meal_sem);
		philo->after_last_meal = get_time();
		sem_post(philo->data->after_last_meal_sem);
		print(philo->data, philo->index, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		print(philo->data, philo->index, "is thinking");
	}
	pthread_join(philo->thread_id, NULL);
	exit(0);
}

int	print(t_philosophers *philosophers, int index, char *message)
{
	int	philos_die;

	sem_wait(philosophers->die_sem);
	philos_die = philosophers->die;
	sem_post(philosophers->die_sem);
	sem_wait(philosophers->print_sem);
	if (!philos_die)
		printf("%llu %d %s\n", get_time() - philosophers->start,
			index + 1, message);
	sem_post(philosophers->print_sem);
	return (1);
}
