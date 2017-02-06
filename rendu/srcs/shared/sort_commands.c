/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 10:04:02 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 12:18:01 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_sx(t_list **head)
{
	t_list *tmp;

	if (!*head || (*head)->next == NULL)
		return ;
	tmp = *head;
	*head = tmp->next;
	tmp->next = (*head)->next;
	(*head)->next = tmp;
}

void	sort_rx(t_list **head)
{
	t_list *tmp;
	t_list *last;

	if (!*head || (*head)->next == NULL)
		return ;
	tmp = *head;
	*head = tmp->next;
	tmp->next = NULL;
	last = *head;
	while (last->next != NULL)
		last = last->next;
	last->next = tmp;
}

void	sort_rrx(t_list **head)
{
	t_list *tmp;
	t_list *last;

	if (!*head || (*head)->next == NULL)
		return ;
	last = *head;
	while (last->next != NULL)
	{
		if (last->next->next == NULL)
			tmp = last;
		last = last->next;
	}
	tmp->next = NULL;
	last->next = *head;
	*head = last;
}

void	sort_px(t_list **head_a, t_list **head_b)
{
	t_list *tmp;

	if (*head_b == NULL)
		return ;
	tmp = (*head_b)->next;
	(*head_b)->next = *head_a;
	*head_a = *head_b;
	*head_b = tmp;
}
