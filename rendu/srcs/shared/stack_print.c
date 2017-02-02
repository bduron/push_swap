/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 10:27:33 by bduron            #+#    #+#             */
/*   Updated: 2017/02/02 10:27:37 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int array_max_min(int argc, char **argv)
{
	int max;
	int min;
	int current;
	int i;

	min = 0;
	max = 0;
	i = 0;
	while (i < argc)
	{
		current = ft_atoi(argv[i++]);
		if (current > max)
			max = current;
		if (current < min)
			min = current;
	}
	return (nb_digit(min) >= nb_digit(max)) ? min : max;
}

int nb_digit(int n)
{
	int len;

	len = (n < 0) ? 1 : 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

size_t lstlen(t_list *list)
{
	size_t len;

	len = 0;
	while (list)
	{
		list = list->next;
		len++;
	}
	return (len);
}

void print_two(t_list *a, t_list *b, int size)
{
	size_t len_a;
	size_t len_b;
	size_t len_diff;
	char big_lst;

	len_a = (a == NULL) ? 0 : lstlen(a);
	len_b = (b == NULL) ? 0 : lstlen(b);
	big_lst = (len_a >= len_b) ? 'a' : 'b';
	len_diff = (big_lst == 'a') ? len_a - len_b : len_b - len_a;
	while (len_diff)
	{
		big_lst == 'a' ? printf(" |%*d|   \n", size, *(int *)a->content)
			: printf(" %*c%*d|\n", size + 5, '|', size, *(int *)b->content);
		a = (big_lst == 'a') ? a->next : a;
		b = (big_lst == 'b') ? b->next : b;
		len_diff--;
	}
	while (a && b)
	{
		printf(" |%*d|  |%*d|\n", size, *(int *)(a->content),
				size, *(int *)b->content);
		a = a->next;
		b = b->next;
	}
	printf(" (%*c)  (%*c) \n\n", size, 'A', size, 'B');
}
