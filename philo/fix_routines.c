/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_routines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:16:38 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/18 16:28:47 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	mutex_help(t_philo *philo, int flag)
{
	if (flag == 0)
		if (!take_lfork(philo))
			return (0);
	if (flag == 1)
		if (!take_rfork(philo))
			return (0);
	if (flag == 2)
	{
		if (philo->flag == 0)
		{
			pthread_mutex_unlock(&philo->fork);
			pthread_mutex_unlock(&philo->next->fork);
		}
		else
		{
			pthread_mutex_unlock(&philo->next->fork);
			pthread_mutex_unlock(&philo->fork);
		}
	}
	return (1);
}

int	take_lfork(t_philo *philo)
{
	if (!check_death(philo))
		return (0);
	print_events(philo, THINKING);
	pthread_mutex_lock(&philo->fork);
	if (!check_death(philo))
		return (pthread_mutex_unlock(&philo->fork), 0);
	print_events(philo, TAKE_FORK);
	if (philo->all->nop == 1)
	{
		pthread_mutex_unlock(&philo->fork);
		return (ft_usleep(philo, philo->ttd), 0);
	}
	pthread_mutex_lock(&philo->next->fork);
	if (!check_death(philo))
		return (mutex_help(philo, 2), 0);
	print_events(philo, TAKE_FORK);
	print_events(philo, EATING);
	init_time(philo);
	ft_usleep(philo, philo->tte);
	return (1);
}

int	take_rfork(t_philo *philo)
{
	if (!check_death(philo))
		return (0);
	print_events(philo, THINKING);
	pthread_mutex_lock(&philo->next->fork);
	if (!check_death(philo))
		return (pthread_mutex_unlock(&philo->next->fork), 0);
	print_events(philo, TAKE_FORK);
	pthread_mutex_lock(&philo->fork);
	if (!check_death(philo))
		return (mutex_help(philo, 2), 0);
	print_events(philo, TAKE_FORK);
	print_events(philo, EATING);
	init_time(philo);
	ft_usleep(philo, philo->tte);
	return (1);
}

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->edit);
	if (philo->all->rip == 1)
	{
		pthread_mutex_unlock(&philo->all->edit);
		return (0);
	}
	pthread_mutex_unlock(&philo->all->edit);
	return (1);
}

void	print_events(t_philo *philo, int flag)
{
	if (flag == DEAD)
		usleep(1000);
	pthread_mutex_lock(&philo->all->print);
	if (flag == THINKING)
		printf("%ld %ld is thinking\n",
			get_time() - philo->all->start, philo->pid);
	else if (flag == TAKE_FORK)
		printf("%ld %ld has taken a fork\n",
			get_time() - philo->all->start, philo->pid);
	else if (flag == EATING)
		printf("%ld %ld is eating\n",
			get_time() - philo->all->start, philo->pid);
	else if (flag == SLEEPING)
		printf("%ld %ld is sleeping\n",
			get_time() - philo->all->start, philo->pid);
	else if (flag == DEAD)
		printf("%ld %ld died\n",
			get_time() - philo->all->start, philo->pid);
	pthread_mutex_unlock(&philo->all->print);
}
