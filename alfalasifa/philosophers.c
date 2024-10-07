/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:16:01 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/08 00:43:33 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// printf("nop -> %ld\n", data.nop);
// printf("ttd -> %ld\n", data.ttd);
// printf("tte -> %ld\n", data.tte);
// printf("tts -> %ld\n", data.tts);
// printf("nom -> %ld\n", data.nom);

int	initialisation(t_var *data, char **av, int ac)
{
	data->nom = -13;
	data->nop = ft_atol(av[1]);
	data->ttd = ft_atol(av[2]);
	data->tte = ft_atol(av[3]);
	data->tts = ft_atol(av[4]);
	if (ac == 6)
		data->nom = ft_atol(av[5]);
	if (data->nom == -1 || data->nop == -1 || data->ttd == -1
		|| data->tte == -1 || data->tts == -1
		|| data->nop == 0 || data->nom == 0)
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
		if (!initialisation(&data, av, ac))
			return (0);
	}
	else
		printf("invalid input\n");
	return (0);
}
