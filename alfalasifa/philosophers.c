/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:16:01 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/08 00:10:03 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// printf("nop -> %ld\n", data.nop);
// printf("ttd -> %ld\n", data.ttd);
// printf("tte -> %ld\n", data.tte);
// printf("tts -> %ld\n", data.tts);
// printf("nom -> %ld\n", data.nom);

void	initialisation(t_var *data, char **av, int ac)
{
	data->nom = -13;
	if (ac == 6)
	{
		data->nop = ft_atol(av[1]);
		data->ttd = ft_atol(av[2]);
		data->tte = ft_atol(av[3]);
		data->tts = ft_atol(av[4]);
		data->nom = ft_atol(av[5]);
	}
	else
	{
		data->nop = ft_atol(av[1]);
		data->ttd = ft_atol(av[2]);
		data->tte = ft_atol(av[3]);
		data->tts = ft_atol(av[4]);
	}
}

int	ft_check(t_var data)
{
	if (data.nom == -1 || data.nop == -1 || data.ttd == -1
		|| data.tte == -1 || data.tts == -1)
	{
		printf("invalid input\n");
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_var	data;

	if (ac >= 5 && ac <= 6)
	{
		initialisation(&data, av, ac);
		if (!ft_check(data) || data.nop == 0 || data.nom == 0)
			return (0);
	}
	else
		printf("invalid input\n");
	return (0);
}
