/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:56:33 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/07 20:06:33 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main()
{
	long 			time;
	long 			time2;
	pthread_t		thrd1;
	pthread_t		thrd2;
	struct timeval 	tv;
	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	printf("time at Start = %ld\n", time);
	sleep(5);
	gettimeofday(&tv, NULL);
	time2 = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	printf("time After Sleep = %ld\n", time2);
	printf("Diff = %ld\n", time2 - time);
	return (42);
}
