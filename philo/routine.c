/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:37:36 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/06/27 17:15:25 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *philo_void)
{
	t_philo			*philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	philo = philo_void;
	if ((philo -> index + 1) % 2 == 0)
		ft_usleep(10);
	if (philo->index == 0)
		left_fork = &(philo->data->forks[philo->data->number_of_philos - 1]);
	else
		left_fork = &(philo->data->forks[philo->index - 1]);
	right_fork = &(philo->data->forks[philo->index]);
	while (1)
	{
		if (!eating(philo, left_fork, right_fork))
			return (0);
		if (!print(philo->data, philo->index, "is sleeping"))
			return (0);
		ft_usleep(philo->data->time_to_sleep);
		if (!print(philo->data, philo->index, "is thinking"))
			return (0);
	}
	return (0);
}

int	eating(t_philo *philo, pthread_mutex_t *l_fork, pthread_mutex_t *r_fork)
{
	if (!taking_forks(philo, &l_fork, &r_fork))
		return (0);
	if (!print(philo->data, philo->index, "is eating"))
	{
		pthread_mutex_unlock(r_fork);
		pthread_mutex_unlock(l_fork);
		return (0);
	}
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(r_fork);
	pthread_mutex_unlock(l_fork);
	pthread_mutex_lock(&(philo->after_last_meal_mutex));
	philo->after_last_meal = get_time();
	pthread_mutex_unlock(&(philo->after_last_meal_mutex));
	pthread_mutex_lock(&(philo->number_of_times_he_ate_mutex));
	philo->number_of_times_he_ate++;
	pthread_mutex_unlock(&(philo->number_of_times_he_ate_mutex));
	return (1);
}

int	print(t_philosophers *philosophers, int index, char *message)
{
	int	dead;
	int	ate;

	pthread_mutex_lock(&(philosophers->dead_philo_mutex));
	dead = philosophers->dead_philo;
	pthread_mutex_unlock(&(philosophers->dead_philo_mutex));
	pthread_mutex_lock(&(philosophers->all_philos_finished_mutex));
	ate = philosophers->all_philos_finished;
	pthread_mutex_unlock(&(philosophers->all_philos_finished_mutex));
	if (dead || ate == (philosophers->number_of_philos))
		return (0);
	pthread_mutex_lock(&(philosophers->print_mutex));
	printf("%ld %d %s\n", get_time() - philosophers->start, index + 1, message);
	pthread_mutex_unlock(&(philosophers->print_mutex));
	return (1);
}

int	taking_forks(t_philo *philo,
	pthread_mutex_t **l_fork, pthread_mutex_t **r_fork)
{
	pthread_mutex_lock(*r_fork);
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
