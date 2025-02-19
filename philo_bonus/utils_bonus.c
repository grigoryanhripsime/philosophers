/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrigrigo <hrigrigo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:37:12 by hrigrigo          #+#    #+#             */
/*   Updated: 2025/02/17 19:34:59 by hrigrigo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	check_num(char *str)
{
	long	num;
	int		i;

	num = 0;
	i = 0;
	while (str[i] && str[i] == '0')
		i++;
	if (ft_strlen(str + i) > 10)
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	if (str[i] || num > 2147483647)
		return (0);
	return (num);
}

long long	get_time(void)
{
	struct timeval	tv;
	static size_t	smt;

	if (smt == 0)
	{
		gettimeofday(&tv, NULL);
		smt = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	}
	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - smt);
}

void	ft_usleep(long long mls)
{
	long long	t;

	t = get_time();
	while (get_time() - t <= mls)
		usleep(500);
}

void	*check(void *philo_void)
{
	t_philo	*philo;

	philo = philo_void;
	while (1)
	{
		finished(philo);
	}
	return (NULL);
}
