/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 10:39:26 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 12:18:38 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*create_stack(int argc, char **argv)
{
	t_list	*head;
	int		i;
	int		val;

	i = argc - 1;
	val = ft_atoi(argv[i--]);
	head = ft_lstnew(&val, sizeof(int));
	while (i > 0)
	{
		val = ft_atoi(argv[i--]);
		ft_lstadd(&head, ft_lstnew(&val, sizeof(int)));
	}
	return (head);
}

int		is_sorted(t_list *stack_a, t_list *stack_b)
{
	int last;

	if (stack_b != NULL)
		return (0);
	last = *(int *)stack_a->content;
	stack_a = stack_a->next;
	while (stack_a)
	{
		if (*(int *)stack_a->content < last)
			return (0);
		last = *(int *)stack_a->content;
		stack_a = stack_a->next;
	}
	return (1);
}

void	ft_lstdel_simple(t_list **alst)
{
	t_list *tmp;

	if (!*alst)
		return ;
	tmp = *alst;
	while (tmp)
	{
		free(tmp->content);
		*alst = tmp->next;
		free(tmp);
		tmp = *alst;
	}
	*alst = NULL;
}
