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

// void	*routine(void *philo_void)
// {
// 	t_philo			*philo;
// 	pthread_mutex_t	*left_fork;
// 	pthread_mutex_t	*right_fork;
// 	philo = philo_void;
// 	if (philo->index == 0)
// 		left_fork = &(philo->data->forks[philo->data->number_of_philos - 1]);
// 	else
// 		left_fork = &(philo->data->forks[philo->index - 1]);
// 	right_fork = &(philo->data->forks[philo->index]);
// 	if ((philo -> index + 1) % 2 == 0)
// 		usleep(500);
// 	while (!finished(philo->data))
// 	{
// 		if (!eating(philo, left_fork, right_fork))
// 			return (0);
// 		print(philo->data, philo->index, "is sleeping");
// 		pthread_mutex_lock(&(philo->after_last_meal_mutex));
// 		philo->after_last_meal = get_time();
// 		pthread_mutex_unlock(&(philo->after_last_meal_mutex));
// 		ft_usleep(philo->data->time_to_sleep);
// 		print(philo->data, philo->index, "is thinking");
// 	}
// 	return (0);
// }

void *check(void *philo_void)
{
	
}

void routine(t_philo *philo)
{
	pthread_create(&philo->thread_id, NULL, check, philo);
	printf("hehe\n");
	exit(0);
}

int	eating(t_philo *philo, pthread_mutex_t *l_fork, pthread_mutex_t *r_fork)
{
	pthread_mutex_lock(r_fork);
	print(philo->data, philo->index, "has taken a fork");
	if (philo->data->number_of_philos == 1)
	{
		pthread_mutex_unlock(r_fork);
		return (0);
	}
	pthread_mutex_lock(l_fork);
	print(philo->data, philo->index, "has taken a fork");
	print(philo->data, philo->index, "is eating");
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(r_fork);
	pthread_mutex_unlock(l_fork);
	pthread_mutex_lock(&(philo->number_of_times_he_ate_mutex));
	philo->number_of_times_he_ate++;
	pthread_mutex_unlock(&(philo->number_of_times_he_ate_mutex));
	return (1);
}

int	print(t_philosophers *philosophers, int index, char *message)
{
	if (finished(philosophers))
		return (0);
	pthread_mutex_lock(&(philosophers->print_mutex));
	printf("%llu %d %s\n", get_time() - philosophers->start,
		index + 1, message);
	pthread_mutex_unlock(&(philosophers->print_mutex));
	return (1);
}

int	taking_forks(t_philo *philo,
	pthread_mutex_t **l_fork, pthread_mutex_t **r_fork)
{
	if (!print(philo->data, philo->index, "has taken a fork")
		|| philo->data->number_of_philos == 1)
	{
		pthread_mutex_unlock(*r_fork);
		return (0);
	}
	pthread_mutex_lock(*l_fork);
	if (!print(philo->data, philo->index, "has taken a fork")
		|| philo->data->number_of_philos == 1)
	{
		pthread_mutex_unlock(*r_fork);
		pthread_mutex_unlock(*l_fork);
		return (0);
	}
	return (1);
}
