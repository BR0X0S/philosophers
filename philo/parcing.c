/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:40:01 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/19 17:06:00 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

int	ft_check_str(char *str)
{
	int	i;
	int	o;

	i = 0;
	o = 0;
	while (str[o] == '0')
		o++;
	while (str[i] != '\0')
		i++;
	if (i - o > 19)
		return (-1);
	return (0);
}

long	ft_atol(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	if (ft_check_str(str) == -1)
		return (-1);
	if (str[i] == '-' || str[i] == '+')
		return (-1);
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i])
		return (-1);
	if (result < 0)
		return (-1);
	return (result);
}

int	initialisation(t_var *data, char **av, int ac)
{
	data->i = 1;
	data->rip = 0;
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
		write(2, "Invalid Input!\n", 15);
		return (0);
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->edit, NULL);
	return (1);
}
