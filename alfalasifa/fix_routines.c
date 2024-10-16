/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_routines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:16:38 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/16 20:18:41 by oumondad         ###   ########.fr       */
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
	if (philo->all->rip == 1)
		return (0);
	printf("philo %ld is thinking\n", philo->pid);
	pthread_mutex_lock(&philo->fork);
	// if (philo->all->rip == 1)
	// 	return (0);
	printf("philo %ld has taken his fork\n", philo->pid);
	pthread_mutex_lock(&philo->next->fork);
	// if (philo->all->rip == 1)
	// 	return (0);
	printf("philo %ld has taken next filo fork\n", philo->pid);
	// if (philo->all->rip == 1)
	// 	return (0);
	printf("philo %ld is eating\n", philo->pid);
	init_time(philo);
	return (1);
}

int	take_rfork(t_philo *philo)
{
	// if (philo->all->rip == 1)
	// 	return (0);
	printf("philo %ld is thinking\n", philo->pid);
	pthread_mutex_lock(&philo->next->fork);
	// if (philo->all->rip == 1)
	// 	return (0);
	printf("philo %ld has taken next filo fork\n", philo->pid);
	pthread_mutex_lock(&philo->fork);
	// if (philo->all->rip == 1)
	// 	return (0);
	printf("philo %ld has taken his fork\n", philo->pid);
	// if (philo->all->rip == 1)
	// 	return (0);
	printf("philo %ld is eating\n", philo->pid);
	init_time(philo);
	return (1);
}
