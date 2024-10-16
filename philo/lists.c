/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:23:36 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/17 19:48:16 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*lst_last(t_philo *head)
{
	if (!head)
		return (NULL);
	while (head && head->next)
		head = head -> next;
	return (head);
}

t_philo	*new_node(t_var	*data)
{
	t_philo	*new_node;

	new_node = malloc(sizeof(t_philo));
	if (data->i == 1)
		data->first_filo = new_node;
	pthread_mutex_init(&new_node->fork, NULL);
	new_node->all = data;
	new_node->tte = data->tte;
	new_node->ttd = data->ttd;
	new_node->tts = data->tts;
	new_node->nom = data->nom;
	new_node->nop = data->nop;
	new_node->pid = data->i;
	if (data->i % 2 == 0)
		new_node->flag = 1;
	else
		new_node->flag = 0;
	if (data->i == data->nop)
		new_node->next = data->first_filo;
	else
		new_node->next = NULL;
	return (new_node);
}

void	lst_add_back(t_philo **head, t_philo *new_node)
{
	t_philo	*last_node;

	if (!head)
		return ;
	last_node = lst_last(*head);
	if (*head)
		last_node->next = new_node;
	else
		*head = new_node;
}

void	creat_list(t_var *data, t_philo **philos)
{
	while (data->i <= data->nop)
	{
		lst_add_back(philos, new_node(data));
		data->i++;
	}
}

void	ft_lstclear(t_philo **lst, t_var *data)
{
	t_philo	*tmp;
	int		i;

	i = 1;
	if (!lst)
		return ;
	while (i <= data->nop)
	{
		tmp = *lst;
		pthread_mutex_destroy(&tmp->fork);
		*lst = (*lst)-> next;
		free (tmp);
		i++;
	}
	tmp = NULL;
}
