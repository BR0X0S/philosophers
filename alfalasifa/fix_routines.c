/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_routines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:16:38 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/17 01:22:22 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->lock_time);
	philo->time = get_time();
	pthread_mutex_unlock(&philo->all->lock_time);
}

int	take_lfork(t_philo *philo)
{
	if (!check_death(philo->all))
		return (0);
	printf("philo %ld is thinking\n", philo->pid);
	pthread_mutex_lock(&philo->fork);
	if (!check_death(philo->all))
		return (pthread_mutex_unlock(&philo->fork), 0);
	printf("philo %ld has taken his fork\n", philo->pid);
	pthread_mutex_lock(&philo->next->fork);
	if (!check_death(philo->all))
		return (mutex_help(&philo, 2), 0);
	printf("philo %ld has taken next filo fork\n", philo->pid);
	printf("philo %ld is eating\n", philo->pid);
	init_time(philo);
	usleep(philo->tte * 1000);
	return (1);
}

int	take_rfork(t_philo *philo)
{
	if (!check_death(philo->all))
		return (0);
	printf("philo %ld is thinking\n", philo->pid);
	pthread_mutex_lock(&philo->next->fork);
	if (!check_death(philo->all))
		return (pthread_mutex_unlock(&philo->next->fork), 0);
	printf("philo %ld has taken next filo fork\n", philo->pid);
	pthread_mutex_lock(&philo->fork);
	if (!check_death(philo->all))
		return (mutex_help(&philo, 2), 0);
	printf("philo %ld has taken his fork\n", philo->pid);
	printf("philo %ld is eating\n", philo->pid);
	init_time(philo);
	usleep(philo->tte * 1000);
	return (1);
}

int	check_death(t_var *data)
{
	pthread_mutex_lock(&data->edit);
	if (data->rip == 1)
	{
		pthread_mutex_unlock(&data->edit);
		return (0);
	}
	pthread_mutex_unlock(&data->edit);
	return (1);
}
