/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:56:33 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/08 19:23:06 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	*rotine(void *args)
{
	t_var *data = (t_var *)args;

	// pthread_mutex_lock(&data->lock);
	data->start = get_time();
	sleep(1);
	data->i++;
	printf("thrd_rotine_done\n");
	data->end = get_time();
	data->total_time = data->end - data->start;
	// pthread_mutex_unlock(&data->lock);
}

void	*rotine2(void *args)
{
	t_var *data = (t_var *)args;

	// pthread_mutex_lock(&data->lock);
	printf("loop%ld thread taken %ld ms\n", data->i, data->total_time);
	// pthread_mutex_unlock(&data->lock);
}

int	main(void)
{
	long			time;
	long			time2;
	pthread_t		thrd1;
	pthread_t		thrd2;
	struct timeval	tv;
	t_var			data;

	data.i = 0;
	pthread_mutex_init(&data.lock, NULL);
	while (data.i < 10)
	{
		pthread_create(&thrd1, NULL, rotine, &data);
		// usleep(1000);
		pthread_join(thrd1, NULL);
		pthread_create(&thrd2, NULL, rotine2, &data);
		pthread_join(thrd2, NULL);
	}
	printf("i = %ld\n", data.i);
	return (0);
}
