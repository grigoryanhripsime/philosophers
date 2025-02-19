/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:37:36 by hrigrigo          #+#    #+#             */
/*   Updated: 2025/02/19 19:25:55 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	routine(t_philo *philo)
{
	pthread_create(&philo->thread_id, NULL, check, philo);
	if ((philo -> index + 1) % 2 == 0)
		usleep(500);
	while (1)
	{
		if (!eating(philo))
			break ;
		print(philo->data, philo->index, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
		print(philo->data, philo->index, "is thinking");
	}
	pthread_join(philo->thread_id, NULL);
	exit(0);
}

int	eating(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print(philo->data, philo->index, "has taken a fork");
	if (philo->data->number_of_philos == 1)
	{
		sem_post(philo->data->forks);
		return (0);
	}
	sem_wait(philo->data->forks);
	print(philo->data, philo->index, "has taken a fork");
	print(philo->data, philo->index, "is eating");
	sem_wait(philo->data->after_last_meal_sem);
	philo->after_last_meal = get_time();
	sem_post(philo->data->after_last_meal_sem);
	ft_usleep(philo->data->time_to_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	sem_wait(philo->data->number_of_times_he_ate_sem);
	philo->number_of_times_he_ate++;
	sem_post(philo->data->number_of_times_he_ate_sem);
	return (1);
}

void	finish_everything(t_philo *philo)
{
	sem_post(philo->data->finish_sem);
	sem_post(philo->data->finish_sem);
	sem_post(philo->data->number_of_times_he_ate_sem);
	sem_post(philo->data->after_last_meal_sem);
	sem_post(philo->data->finish_sem);
	sem_post(philo->data->number_of_times_he_ate_sem);
	sem_post(philo->data->after_last_meal_sem);
}

void	finished(t_philo *philo)
{
	sem_wait(philo->data->after_last_meal_sem);
	if ((get_time() - philo->after_last_meal)
		>= philo->data->time_to_die)
	{
		sem_wait(philo->data->print_sem);
		printf("%llu %d %s\n", get_time() - philo->data->start,
			philo->index + 1, "died");
		sem_wait(philo->data->finish_sem);
		philo->data->finish = 1;
		sem_post(philo->data->finish_sem);
		sem_post(philo->data->after_last_meal_sem);
		exit(1);
	}
	sem_post(philo->data->after_last_meal_sem);
	sem_wait(philo->data->number_of_times_he_ate_sem);
	if (philo->number_of_times_he_ate
		== philo->data->number_philos_must_eat)
	{
		sem_post(philo->data->number_of_times_he_ate_sem);
		sem_wait(philo->data->finish_sem);
		philo->data->finish = 1;
		finish_everything(philo);
		exit(0);
	}
	sem_post(philo->data->number_of_times_he_ate_sem);
}

int	print(t_philosophers *philosophers, int index, char *message)
{
	sem_wait(philosophers->print_sem);
	sem_wait(philosophers->finish_sem);
	if (philosophers->finish == 1)
	{
		sem_post(philosophers->print_sem);
		sem_post(philosophers->finish_sem);
		return (0);
	}
	sem_post(philosophers->finish_sem);
	printf("%llu %d %s\n", get_time() - philosophers->start,
		index + 1, message);
	sem_post(philosophers->print_sem);
	return (1);
}
