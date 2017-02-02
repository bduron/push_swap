/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_quartile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 14:17:17 by bduron            #+#    #+#             */
/*   Updated: 2017/02/02 14:36:29 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int *find_quartiles(int *arr, int size, int nb)
{
	int *quartiles;
	int i;
	int j;

	quartiles = (int *)malloc(sizeof(int) * nb);
	i = 0;
	j = 0;
	while (i < size && j < nb)
	{
		i = i + size / (nb + 1);
		quartiles[j] = arr[i];
		j++;
	}
	return (quartiles);
}

t_sort *launch_fquar(t_sort *s)
{
	int i;
	int max;
	int best_cmd;
	int next;

	s->sa = create_stack(s->cargc, s->cargv);
	s->sb = NULL;
	i = 0;
	if (!is_sorted(s->sa, s->sb))
	{
		while (s->sa)
		{
			if (*(int *)s->sa->content <= s->quarts[i])
				launch_wrapper(s, "pb", 0);
			else if (*(int *)s->sa->content > s->quarts[s->nb_quarts - 1 - i])
			{
				launch_wrapper(s, "pb", 0);
				launch_wrapper(s, "rb", 0);
			}
			if (quarts_rem(s->sa, s->quarts[i], s->quarts[s->nb_quarts - 1 - i]) == 0)
				i++;
			next = find_quartile(s->sa, s->quarts[i], s->quarts[s->nb_quarts - 1 - i]);
			best_cmd = rrx_or_rx(s->sa, next);
			if (best_cmd == 0)
				while (*(int *)s->sa->content != next)
					launch_wrapper(s, "rra", 0);
			else if (best_cmd == 1)
				while (*(int *)s->sa->content != next)
					launch_wrapper(s, "ra", 0);
		}
		launch_wrapper(s, "pb", 0);
		while (s->sb != NULL)
		{
			max = find_max(s->sb);
			best_cmd = rrx_or_rx(s->sb, max);
			if (best_cmd == 0)
				while (*(int *)s->sb->content != max)
					launch_wrapper(s, "rrb", 0);
			else if (best_cmd == 1)
				while (*(int *)s->sb->content != max)
					launch_wrapper(s, "rb", 0);
			launch_wrapper(s, "pa", 0);
		}
	}
	ft_lstdel_simple(&(s->sa));
	return (s);
}

int quarts_rem(t_list *s, int lower, int upper)
{
	if (!s)
		return (-1);
	while (s)
	{
		if (*(int *)s->content <= lower || *(int *)s->content > upper)
			return (1);
		s = s->next;
	}
	return (0);
}

int find_quartile(t_list *s, int lower, int upper)
{
	int first;
	int last;
	int first_i;
	int last_i;
	int i;

	if (!s || !s->next)
		return (-1);
	first_i = 0;
	last_i = 0;
	i = 0;
	first = -1;
	last = -1;
	while (s)
	{
		if (first == -1 && 
				(*(int *)s->content > upper || *(int *)s->content <= lower))
			first = *(int *)s->content;
		if (first == -1)
			first_i++;
		if (*(int *)s->content > upper || *(int *)s->content <= lower)
		{
			last = *(int *)s->content;
			last_i = i;
		}
		i++;
		s = s->next;
	}
	return (first_i < (i - last_i)) ? first : last;
}
