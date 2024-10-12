/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:16:01 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/12 17:10:11 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	initialisation(t_var *data, char **av, int ac)
{
	data->i = 1;
	data->first_filo = NULL;
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

void	creat_list(t_var *data, t_philo **philos)
{
	while (data->i <= data->nop)
	{
		lst_add_back(philos, new_node(data));
		data->i++;
	}
}

void	print_list(t_philo	*philos)
{
	int	i;

	i = 0;
	while (i)
	{
		printf("-----------------\n");
		printf("pid: |%ld|\n", philos->pid);
		printf("ttd: |%ld|\n", philos->ttd);
		printf("tte: |%ld|\n", philos->tte);
		printf("tts: |%ld|\n", philos->tts);
		printf("nom: |%ld|\n", philos->nom);
		printf("nop: |%ld|\n", philos->nop);
		printf("-----------------\n");
		philos = philos->next;
		sleep(1);
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
		print_list(data.first_filo);
		// start_simulation(&data);
		ft_lstclear(&philos, &data);
	}
	else
	{
		printf("Invalid Number of Args!\n");
		return (1);
	}
	return (0);
}
