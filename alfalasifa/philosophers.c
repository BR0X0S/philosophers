/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:16:01 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/17 18:23:34 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	init_time(philo);
	if (philo->flag == 1)
		usleep(500);
	while (1)
	{
		if (!mutex_help(philo, philo->flag))
			return (NULL);
		mutex_help(philo, 2);
		if (!check_death(philo))
			return (NULL);
		pthread_mutex_lock(&philo->all->edit);
		if (philo->nom > 0)
			philo->nom--;
		if (philo->nom == 0)
			return (pthread_mutex_unlock(&philo->all->edit), NULL);
		pthread_mutex_unlock(&philo->all->edit);
		print_events(philo, SLEEPING);
		ft_usleep(philo, philo->tts);
	}
}

int	all_done(t_philo *philo, t_var *data)
{
	t_philo	*tmp;

	tmp = philo;
	(void)data;
	pthread_mutex_lock(&philo->all->edit);
	while (1)
	{
		if (philo->nom > 0)
			return (pthread_mutex_unlock(&philo->all->edit), 1);
		philo = philo->next;
		if (philo == tmp)
			return (pthread_mutex_unlock(&philo->all->edit), 0);
	}
}

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
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
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
		pthread_mutex_lock(&philo->all->edit);
		if ((get_time() - philo->time) > philo->ttd && philo->nom)
		{
			philo->all->rip = 1;
			pthread_mutex_unlock(&philo->all->edit);
			print_events(philo, DEAD);
			return (NULL);
		}
		if (philo->nom >= 0)
		{
			pthread_mutex_unlock(&philo->all->edit);
			if (!all_done(philo, philo->all))
				return (pthread_mutex_unlock(&philo->all->edit), NULL);
		}
		pthread_mutex_unlock(&philo->all->edit);
		usleep(500);
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
	pthread_join(data->waitress, NULL);
}

void	start_simulation(t_var *data, t_philo *philos)
{
	int		i;
	t_philo	*current_philo;

	i = 1;
	data->start = get_time();
	current_philo = philos;
	while (i <= data->nop)
	{
		pthread_create(&current_philo->philo, NULL, &routine,
			(void *)current_philo);
		current_philo = current_philo->next;
		i++;
	}
	pthread_create(&data->waitress, NULL, &check_rip, (void *)current_philo);
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
