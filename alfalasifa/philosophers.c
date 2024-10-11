/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:16:01 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/11 16:44:16 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	initialisation(t_var *data, char **av, int ac)
{
	data->nop = ft_atol(av[1]);
	data->ttd = ft_atol(av[2]);
	data->tte = ft_atol(av[3]);
	data->tts = ft_atol(av[4]);
	data->nom = -13;
	if (ac == 6)
		data->nom = ft_atol(av[5]);
	if (data->nom == -1 || data->nop == -1 || data->ttd == -1
		|| data->tte == -1 || data->tts == -1)
	{
		printf("Invalid Input!\n");
		return (0);
	}
	return (1);
}

void	creat_list(t_var *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->nop)
	{
		lst_add_back(&philo, new_node(data));
		i++;
	}
}

void	print_list(t_philo	*philos)
{
	t_philo	*tmp;

	tmp = philos;
	while (tmp)
	{
		printf("pid: %ld\n", tmp->pid);
		tmp = tmp->next;
		usleep(50000);
	}
}

int	main(int ac, char **av)
{
	t_var	data;

	if (ac == 5 || ac == 6)
	{
		if (!initialisation(&data, av, ac))
			return (1);
		if (data.nop == 0 || data.nom == 0)
			return (0);
		creat_list(&data);
		print_list(data.first_filo);
		// start_simulation(&data);
	}
	else
	{
		printf("Invalid Number of Args!\n");
		return (1);
	}
	return (0);
}
