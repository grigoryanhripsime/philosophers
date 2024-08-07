/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:37:31 by hrigrigo          #+#    #+#             */
/*   Updated: 2024/08/07 13:05:40 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	close_unlink(t_philosophers *philos)
{
	sem_close(philos->after_last_meal_sem);
	sem_unlink("/last_meal");
	sem_close(philos->number_of_times_he_ate_sem);
	sem_unlink("/num_he_ate");
	sem_close(philos->forks);
	sem_unlink("/forks");
	sem_close(philos->print_sem);
	sem_unlink("/print");
	sem_close(philos->die_sem);
	sem_unlink("/die");
}

int	main(int argc, char *argv[])
{
	t_philosophers	*philos;

	if (argc != 5 && argc != 6)
		return (printf("Error!!\nInvalid number of arguments.\n"));
	philos = init(argc, argv);
	if (!philos)
		return (printf("Invalid Argument!!!\n"));
	if (philos->number_philos_must_eat == 0)
		return (0);
	close_unlink(philos);
	semaphores(philos);
	create_philos(philos);
	printf("Im here111\n");
	close_destroy(philos);
	return (0);
}

void	close_destroy(t_philosophers *philos)
{
	int	i;
	int	exit;

	i = 0;
	while (i < philos -> number_of_philos)
	{
		waitpid(-1, &exit, 0);
		if (WEXITSTATUS(exit) > 0)
		{
			i = 0;
			while (i < philos->number_of_philos)
			{
				kill(philos->philos[i].pid, SIGKILL);
				i++;
			}
			break ;
		}
		i++;
	}
	close_unlink(philos);
	free(philos->philos);
	free(philos);
}
