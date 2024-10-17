/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:16:06 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/17 01:23:33 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_mutex_t	fork;
	pthread_t		philo;
	struct s_var	*all;
	int				flag;
	long			time;
	long			pid;
	long			ttd;
	long			tte;
	long			tts;
	long			nom;
	long			nop;
	struct s_philo	*next;
}	t_philo;

typedef struct s_var
{
	t_philo			*first_filo;
	pthread_t		waitress;
	long			total_time;
	long			start;
	long			end;
	long			nop;
	long			ttd;
	long			tte;
	long			tts;
	long			nom;
	long			i;
	long			rip;
	pthread_mutex_t	edit;
	pthread_mutex_t	lock_time;
}	t_var;

t_philo	*new_node(t_var	*data);
long	ft_atol(char *str);
long	get_time(void);
void	lst_add_back(t_philo **head, t_philo *new_node);
void	ft_lstclear(t_philo **lst, t_var *data);
int		initialisation(t_var *data, t_philo *philo, char **av, int ac);
void	creat_list(t_var *data, t_philo **philos);
void	print_list(t_philo	*philos);
void	init_time(t_philo *philo);
int		mutex_help(t_philo **philo, int flag);
int		take_lfork(t_philo *philo);
int		take_rfork(t_philo *philo);
int		check_death(t_var *data);

#endif