/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:37:31 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/06/30 19:11:22 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char *argv[])
{
	t_philosophers	*philos;

	if (argc != 5 && argc != 6)
		return (printf("Error!!\nInvalid number of arguments.\n"));
	philos = init(argc, argv);
	if (!philos)
		return (printf("Invalid Argument!!!\n"));

	//mutex_inits(philos);
	printf("%d\n", __LINE__);
	semaphores(philos);
	printf("%d\n", __LINE__);
	create_philos(philos);
	printf("%d\n", __LINE__);
	close_destroy(philos);
}

// int	check_dead(t_philosophers *philos)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philos->number_of_philos)
// 	{
// 		pthread_mutex_lock(&(philos->philos[i].after_last_meal_mutex));
// 		if ((get_time() - philos->philos[i].after_last_meal)
// 			>= philos->time_to_die)
// 		{
// 			pthread_mutex_lock(&(philos->finish_mutex));
// 			philos->finish = 1;
// 			pthread_mutex_unlock(&(philos->finish_mutex));
// 			pthread_mutex_lock(&(philos->print_mutex));
// 			printf("%llu %d %s\n", get_time() - philos->start, i + 1, "died");
// 			pthread_mutex_unlock(&(philos->print_mutex));
// 			pthread_mutex_unlock(&(philos->philos[i].after_last_meal_mutex));
// 			return (1);
// 		}
// 		pthread_mutex_unlock(&(philos->philos[i].after_last_meal_mutex));
// 		i++;
// 	}
// 	return (0);
// }

// int	check_eaten(t_philosophers *philos)
// {
// 	int	i;
// 	int	all_philos_finished;

// 	if (philos->number_philos_must_eat < 0)
// 		return (0);
// 	i = 0;
// 	all_philos_finished = 0;
// 	while (i < philos->number_of_philos)
// 	{
// 		pthread_mutex_lock(&(philos->philos[i].number_of_times_he_ate_mutex));
// 		if (philos->philos[i].number_of_times_he_ate
// 			>= philos->number_philos_must_eat)
// 			all_philos_finished++;
// 		pthread_mutex_unlock(&(philos->philos[i].number_of_times_he_ate_mutex));
// 		i++;
// 	}
// 	if (all_philos_finished == philos->number_of_philos)
// 	{
// 		pthread_mutex_lock(&(philos->finish_mutex));
// 		philos->finish = 1;
// 		pthread_mutex_unlock(&(philos->finish_mutex));
// 		return (1);
// 	}
// 	return (0);
// }

void	close_destroy(t_philosophers *philos)
{
	int	i;
	int exit;

	i = 0;
	while (i < philos -> number_of_philos)
	{
		waitpid(-1, &exit, 0);
		if (WEXITSTATUS(exit) > 0)
		{
			i = 0;
			while (i < philos->number_of_philos)
				kill(philos->philos[i].pid, SIGKILL);
			break ;
		}
		sem_close(philos->philos[i].after_last_meal_sem);
		sem_unlink("/last_meal");
		sem_close(philos->philos[i].number_of_times_he_ate_sem);
		sem_unlink("/num_he_ate");
		i++;
	}
	sem_close(philos->forks);
	sem_unlink("/forks");
	sem_close(philos->print_sem);
	sem_unlink("/print");
	free(philos->philos);
	free(philos);
}


// 	finished(t_philosophers *philos)
// {
// 	int	finished;

// 	while (1)
// 	{
// 		if (check_dead(philos))
// 			return (1);
// 		if (check_eaten(philos))
// 			break ;
// 	}
// 	return (finished);
// }