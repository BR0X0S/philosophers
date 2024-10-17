/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:50:30 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/17 19:51:00 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->edit);
	philo->time = get_time();
	pthread_mutex_unlock(&philo->all->edit);
}

void	ft_usleep(t_philo *philo, long t)
{
	long	time;

	time = get_time();
	while (get_time() - time < t)
	{
		pthread_mutex_lock(&philo->all->edit);
		if (philo->all->rip == 1)
		{
			pthread_mutex_unlock(&philo->all->edit);
			break ;
		}
		pthread_mutex_unlock(&philo->all->edit);
		usleep(500);
	}
}

void	join_threads(t_var *data, t_philo *philos)
{
	int	i;

	i = 1;
	while (i <= data->nop)
	{
		pthread_join(philos->philo, NULL);
		philos = philos->next;
		i++;
	}
	pthread_join(data->waitress, NULL);
}
