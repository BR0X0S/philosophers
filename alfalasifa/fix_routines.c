/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_routines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:16:38 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/17 18:23:59 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->edit);
	philo->time = get_time();
	pthread_mutex_unlock(&philo->all->edit);
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
	pthread_mutex_lock(&philo->all->print);
	if (flag == THINKING)
		printf("%ld %ld is thinking\n", get_time() - philo->all->start, philo->pid);
	else if (flag == TAKE_FORK)
		printf("%ld %ld has taken a fork\n", get_time() - philo->all->start, philo->pid);
	else if (flag == EATING)	
		printf("%ld %ld is eating\n", get_time() - philo->all->start, philo->pid);
	else if (flag == SLEEPING)
		printf("%ld %ld is sleeping\n", get_time() - philo->all->start, philo->pid);
	else if (flag == DEAD)
		printf("%ld %ld died\n", get_time() - philo->all->start, philo->pid);
	pthread_mutex_unlock(&philo->all->print);
}

void    ft_usleep(t_philo *philo, long t)
{
    long    time;

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
