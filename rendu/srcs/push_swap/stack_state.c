/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 14:03:36 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 15:02:32 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		is_near_sorted(t_sort *s)
{
	int		min;
	int		max;
	int		first;
	t_list	*tmp;

	tmp = s->sa;
	min = s->arr[0];
	max = s->arr[s->cargc - 2];
	first = *(int *)tmp->content;
	while (tmp->next)
	{
		if (*(int *)tmp->content == max
				&& *(int *)tmp->next->content == min)
			tmp = tmp->next;
		if (!tmp->next)
			break ;
		if (*(int *)tmp->content > *(int *)tmp->next->content)
			return (0);
		tmp = tmp->next;
	}
	if (*(int *)tmp->content > first)
		if (*(int *)tmp->content != max || first != min)
			return (0);
	return (1);
}

int		is_reverse(t_list *stack)
{
	while (stack->next)
	{
		if (*(int *)stack->content < *(int *)stack->next->content)
			return (0);
		stack = stack->next;
	}
	return (1);
}

int		rrx_or_rx(t_list *s, int min)
{
	int min_index;
	int stack_len;

	if (!s || !s->next)
		return (2);
	stack_len = 0;
	min_index = 0;
	while (s)
	{
		if (*(int *)s->content == min)
			min_index = stack_len;
		stack_len++;
		s = s->next;
	}
	return (min_index * 100 / stack_len > 50) ? 0 : 1;
}

int		find_max(t_list *s)
{
	int max;

	if (!s || !s->next)
		return (-1);
	max = *(int *)s->content;
	while (s)
	{
		max = (*(int *)s->content > max) ? *(int *)s->content : max;
		s = s->next;
	}
	return (max);
}
