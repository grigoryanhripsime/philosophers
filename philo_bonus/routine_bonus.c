/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:37:36 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/06/30 20:02:17 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void *check(void *philo_void)
{
	t_philo *philo;

	philo = philo_void;
	while (1)
	{
		//if philo died
		sem_wait(philo->after_last_meal_sem);
		if ((get_time() - philo->after_last_meal)
			>= philo->data->time_to_die)
		{
			sem_post(philo->after_last_meal_sem);
			exit(1);		
		}
		sem_post(philo->after_last_meal_sem);
		//if ate
		sem_wait(philo->number_of_times_he_ate_sem);
		if (philo->number_of_times_he_ate >= philo->data->number_philos_must_eat)
		{
			sem_post(philo->number_of_times_he_ate_sem);
			exit(0);
		}
		sem_post(philo->number_of_times_he_ate_sem);
	}
	return (NULL);
}

void routine(t_philo *philo)
{
	pthread_create(&philo->thread_id, NULL, check, philo);
	printf("hehe\n");
	if ((philo -> index + 1) % 2 == 0)
		usleep(500);
	while(1)
	{
		if (!eating(philo))
			return ;
		print(philo->data, philo->index, "is sleeping");
		sem_wait(philo->after_last_meal_sem);
		philo->after_last_meal = get_time();
		sem_post(philo->after_last_meal_sem);
		ft_usleep(philo->data->time_to_sleep);
		print(philo->data, philo->index, "is thinking");
	}
	pthread_join(philo->thread_id, NULL);
	exit(0);
}

int	eating(t_philo *philo)
{
	taking_forks(philo);
	print(philo->data, philo->index, "is eating");
	ft_usleep(philo->data->time_to_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	sem_wait(philo->number_of_times_he_ate_sem);
	philo->number_of_times_he_ate++;
	sem_post(philo->number_of_times_he_ate_sem);
	return (1);
}

int	print(t_philosophers *philosophers, int index, char *message)
{
	// if (finished(philosophers))
	// 	return (0);
	sem_wait(philosophers->print_sem);
	printf("%llu %d %s\n", get_time() - philosophers->start,
		index + 1, message);
	sem_post(philosophers->print_sem);
	return (1);
}

int	taking_forks(t_philo *philo)
{
	if (sem_wait(philo->data->forks) < 0)
		return (0);
	if (!print(philo->data, philo->index, "has taken a fork")
		|| philo->data->number_of_philos == 1)
	{
		sem_post(philo->data->forks);
		return (0);
	}
	if (sem_wait(philo->data->forks) < 0)
		return (0);
	if (!print(philo->data, philo->index, "has taken a fork"))
	{
		sem_post(philo->data->forks);
		sem_post(philo->data->forks);
		return (0);
	}
	return (1);
}
