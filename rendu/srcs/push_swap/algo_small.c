/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 14:43:41 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 14:30:19 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	launch_small_next(t_sort *s, int min, int best_cmd)
{
	int next;
	int max;

	max = s->arr[s->cargc - 2];
	while (!is_near_sorted(s))
	{
		if (*(int *)s->sa->content > *(int *)s->sa->next->content
				&& (*(int *)s->sa->content != max
					|| *(int *)s->sa->next->content != min))
			launch_wrapper(s, "sa", 0);
		else
		{
			next = find_unsorted(s, 0, 0);
			best_cmd = rrx_or_rx(s->sa, next);
			if (best_cmd == 0)
				while (*(int *)s->sa->content != next)
					launch_wrapper(s, "rra", 0);
			else if (best_cmd == 1)
				while (*(int *)s->sa->content != next)
					launch_wrapper(s, "ra", 0);
		}
	}
}

t_sort	*launch_small(t_sort *s)
{
	int min;
	int best_cmd;

	best_cmd = 0;
	min = s->arr[0];
	s->sa = create_stack(s->cargc, s->cargv);
	s->sb = NULL;
	launch_small_next(s, min, best_cmd);
	while (!is_sorted(s->sa, s->sb))
	{
		best_cmd = rrx_or_rx(s->sa, min);
		if (best_cmd == 0)
			while (*(int *)s->sa->content != min)
				launch_wrapper(s, "rra", 0);
		else if (best_cmd == 1)
			while (*(int *)s->sa->content != min)
				launch_wrapper(s, "ra", 0);
	}
	ft_lstdel_simple(&(s->sa));
	return (s);
}

t_sort	*launch_reverse(t_sort *s)
{
	s->sa = create_stack(s->cargc, s->cargv);
	s->sb = NULL;
	while (!is_sorted(s->sa, s->sb))
	{
		launch_wrapper(s, "rra", 0);
		launch_wrapper(s, "rra", 0);
		launch_wrapper(s, "pb", 0);
		launch_wrapper(s, "pb", 0);
		launch_wrapper(s, "rr", 0);
		launch_wrapper(s, "sa", 0);
		launch_wrapper(s, "pa", 0);
		launch_wrapper(s, "pa", 0);
	}
	ft_lstdel_simple(&(s->sa));
	return (s);
}

int		find_unsorted(t_sort *s, int last, int i)
{
	int		last_i;
	int		first;
	t_list	*tmp;

	last_i = 2000000000;
	first = *(int *)s->sa->content;
	tmp = s->sa;
	while (tmp->next)
	{
		if (*(int *)tmp->content != s->arr[s->cargc - 2]
				|| *(int *)tmp->next->content != s->arr[0])
			if (*(int *)tmp->content > *(int *)tmp->next->content)
				if (s->cargc - 1 - i < last_i)
				{
					last = *(int *)tmp->content;
					last_i = i;
				}
		i++;
		tmp = tmp->next;
	}
	if (*(int *)tmp->content != s->arr[s->cargc - 2] || first != s->arr[0])
		if (*(int *)tmp->content > first)
			return (*(int *)tmp->content);
	return (last);
}
