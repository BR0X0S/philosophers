/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:16:01 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/16 20:28:30 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	init_time(philo);
	if (philo->flag == 1)
		usleep((philo->tte - 20) * 1000);
	while (1)
	{
		if (!mutex_help(&philo, philo->flag))
			return (NULL);
		usleep(philo->tte * 1000);
		init_time(philo);
		if (!(philo->nom < 0))
			philo->nom--;
		if (philo->nom == 0)
		{
			mutex_help(&philo, 2);
			break ;
		}
		mutex_help(&philo, 2);
		printf("philo %ld is sleeping\n", philo->pid);
		usleep(philo->tts * 1000);
	}
	return (NULL);
}

int	mutex_help(t_philo **philo, int flag)
{
	if (flag == 0)
		if (!take_lfork(*philo))
			return (0);
	if (flag == 1)
		if (!take_rfork(*philo))
			return (0);
	if (flag == 2)
	{
		pthread_mutex_unlock(&(*philo)->fork);
		pthread_mutex_unlock(&(*philo)->next->fork);
	}
	return (1);
}

void	*check_rip(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->all->lock_time);
		if ((get_time() - philo->time) > philo->ttd)
		{
			pthread_mutex_lock(&philo->all->edit);
			philo->all->rip = 1;
			printf("philo number %ld is died\n", philo->pid);
			pthread_mutex_unlock(&philo->all->edit);
			pthread_mutex_unlock(&philo->all->lock_time);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->all->lock_time);
		philo = philo->next;
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
}

void	start_simulation(t_var *data, t_philo *philos)
{
	int		i;
	t_philo	*current_philo;

	i = 1;
	current_philo = philos;
	while (i <= data->nop)
	{
		pthread_create(&current_philo->philo, NULL, &routine,
			(void *)current_philo);
		current_philo = current_philo->next;
		i++;
	}
	pthread_create(&data->waitress, NULL, check_rip, (void *)current_philo);
}

int	main(int ac, char **av)
{
	t_var	data;
	t_philo	*philos;

	philos = NULL;
	if (ac == 5 || ac == 6)
	{
		if (!initialisation(&data, philos, av, ac))
			return (1);
		if (data.nop == 0 || data.nom == 0)
			return (0);
		creat_list(&data, &philos);
		// print_list(data.first_filo);
		start_simulation(&data, philos);
		join_threads(&data, philos);
		ft_lstclear(&philos, &data);
	}
	else
	{
		printf("Invalid Number of Args!\n");
		return (1);
	}
	return (0);
}
