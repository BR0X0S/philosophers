/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oumondad <oumondad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:23:36 by oumondad          #+#    #+#             */
/*   Updated: 2024/10/10 18:49:41 by oumondad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_desk	*lst_last(t_desk *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head -> next;
	return (head);
}

t_desk	*new_node(t_var	*data)
{
	t_desk	*new_node;

	new_node = malloc(sizeof(t_desk));
	if (data->i == 0)
		data->first_filo = new_node;
	pthread_mutex_init(&new_node->fork, NULL);
	new_node->data = data;
	if (data->i == data->nop)
		new_node->next = data->first_filo;
	else
		new_node->next = NULL;
	return (new_node);
}

void	lst_add_back(t_desk **head, t_desk *new_node)
{
	t_desk	*last_node;

	if (!head)
		return ;
	last_node = lst_last(*head);
	if (*head)
		last_node->next = new_node;
	else
		*head = new_node;
}

void	ft_lstclear(t_desk **lst, t_var *data)
{
	t_desk	*tmp;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		tmp = *lst;
		//
		*lst = (*lst)-> next;
		free (tmp);
	}
	tmp = NULL;
}
