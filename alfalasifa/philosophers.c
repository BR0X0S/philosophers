/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:16:01 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/13 16:40:16 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	printf("here\n");
	philo = (t_philo *)arg;
	while (1)
	{
		printf("philo %ld is thinking\n", philo->pid);
		pthread_mutex_lock(&philo->fork);
		printf("philo %ld has taken his fork\n", philo->pid);
		pthread_mutex_lock(&philo->next->fork);
		printf("philo %ld has taken next filo fork\n", philo->pid);
		printf("philo %ld is eating\n", philo->pid);
		if (!(philo->nom < 0))
			philo->nom--;
		if (philo->nom == 0)
			break ;
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		printf("philo %ld is sleeping\n", philo->pid);
		usleep(10000);
	}
	return (NULL);
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
}

int	main(int ac, char **av)
{
	t_var	data;
	t_philo	*philos;

	philos = NULL;
	if (ac == 5 || ac == 6)
	{
		if (!initialisation(&data, av, ac))
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
