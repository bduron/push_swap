/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 08:50:53 by bduron            #+#    #+#             */
/*   Updated: 2017/02/02 10:51:45 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>


/**************** Main  Checker **********************/



int is_near_sorted(t_sort *s)
{ 
	int min;
	int max;
	int first;
	t_list *tmp;

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
			break;
		if (*(int *)tmp->content > *(int *)tmp->next->content)
			return (0);
		tmp = tmp->next;
	}
	if (*(int *)tmp->content > first)
		if (*(int *)tmp->content != max || first != min)
			return (0);
	return (1);		
}	


int is_reverse(t_list *stack)
{ 
	while (stack->next)
	{
		if (*(int *)stack->content < *(int *)stack->next->content)
			return (0);
		stack = stack->next;
	}	
	return (1);
}	


/************************* PS  -  launch sorting algorithms wrapper ***************************/

void launch_wrapper(t_sort *s, char *cmd, int print)
{
	launch_sort(&s->sa, &s->sb, cmd);
	s->nb_cmd++;	
	if (print)
	{
		print_two(s->sa, s->sb, nb_digit(array_max_min(s->cargc, s->cargv)));  
	}
		ft_lstaddback(&s->cmd_lst, ft_lstnew(cmd, sizeof(char) * 4));			
}

/************************* PS  -  launch sorting algorithms ***************************/

int rrx_or_rx(t_list *s, int min)
{
	int	min_index;
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

int find_max(t_list *s)
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


int find_unsorted(t_sort *s)
{	
	int last;
	int last_i;
	int i;
	int first;
	t_list *tmp;

	i = 0;
	last = 0;
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


t_sort *launch_small(t_sort *s)
{
	int min;
	int max;
	int next;
	int best_cmd;

	min = s->arr[0];
	max = s->arr[s->cargc - 2];
	s->sa = create_stack(s->cargc, s->cargv);	
	s->sb = NULL;
	while (!is_near_sorted(s))
	{
		if (*(int *)s->sa->content > *(int *)s->sa->next->content
				&& (*(int *)s->sa->content != max 
					|| *(int *)s->sa->next->content != min))
			launch_wrapper(s, "sa", 0);
		else 
		{	
			next = find_unsorted(s);
			best_cmd = rrx_or_rx(s->sa, next);
			if (best_cmd == 0)
				while (*(int *)s->sa->content != next)
					launch_wrapper(s, "rra", 0);
			else if (best_cmd == 1)
				while (*(int *)s->sa->content != next)
					launch_wrapper(s, "ra", 0);
		}
	}
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

t_sort *launch_reverse(t_sort *s)
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

void print_cmd(t_list *cmd)
{
	while (cmd)
	{
		printf("%s\n", (char *)cmd->content);	
		cmd = cmd->next; 	
	}	
}

void launch_all_sorts(t_sort **s)
{
	t_sort *cmd;

	s[0]->srev = create_stack((s[0])->cargc, (s[0])->cargv);	
	if (is_reverse((*s)->srev) && (*s)->cargc - 1 == 5)
		cmd = launch_reverse(s[2]);
	else if ((*s)->cargc - 1 < 30)
		cmd = launch_small(s[1]);
	else  
		cmd = launch_fquar(s[4]);
	print_cmd(cmd->cmd_lst);
	ft_lstdel_simple(&(cmd->cmd_lst));
	ft_lstdel_simple(&(s[0]->srev));
}

/********* generate array, quicksort it, find median ************/


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


/////////////////// FIND MEDIAN ///////////////////

int *arr_to_sort(int argc, char **argv)
{
	int *arr;
	int i;

	arr = (int *)malloc(sizeof(int) * argc - 1);
	i = 0;
	while (i < argc - 1)
	{
		arr[i] = ft_atoi(argv[i + 1]);
		i++;
	}	
	return (arr);
}

void swap(int *a, int *b)
{
	int swap;

	swap = *a;
	*a = *b;
	*b = swap;
}

int partionning(int *arr, int start, int end)
{
	int pindex;
	int pivot;
	int i;

	pindex = start;
	pivot = arr[end];
	i = start ;
	while (i < end)
	{
		if (arr[i] <= pivot)
		{
			swap(&arr[i], &arr[pindex]);
			pindex++;
		}
		i++;
	}
	swap(&arr[end], &arr[pindex]); 
	return (pindex);
}

int *quicksort(int *arr, int start, int end)
{
	int pindex;

	if (start >= end)
		return (0);
	pindex = partionning(arr, start, end);
	quicksort(arr, start, pindex - 1);
	quicksort(arr, pindex + 1, end);
	return (arr);
}



/************************* PS  -  init_sorts  ***************************/


t_sort *init_reverse(int argc, char **argv, int *flag)
{
	t_sort *reverse;

	if ((reverse = (t_sort *)malloc(sizeof(t_sort))) == 0)
		return (NULL);		
	reverse->name = "Small sort";
	reverse->nb_cmd = 0;
	reverse->cargc = argc; 
	reverse->cargv = argv;
	reverse->cflag = flag;
	reverse->cmd_lst = NULL;
	reverse->sa = NULL;  
	reverse->sb = NULL;  
	return (reverse);
}

t_sort *init_small(int argc, char **argv, int *flag)
{
	t_sort *small;

	if ((small = (t_sort *)malloc(sizeof(t_sort))) == 0)
		return (NULL);		
	small->name = "Small sort";
	small->nb_cmd = 0;
	small->cargc = argc; 
	small->cargv = argv;
	small->cflag = flag;
	small->cmd_lst = NULL;
	small->sa = NULL;  
	small->sb = NULL;  
	small->arr = arr_to_sort(argc, argv);	
	quicksort(small->arr, 0, argc - 2);	
	return (small);
}

t_sort *init_fquar(int argc, char **argv, int *flag)
{
	t_sort *fquar;

	if ((fquar = (t_sort *)malloc(sizeof(t_sort))) == 0)
		return (NULL);		
	fquar->name = "Find quartiles sort";
	fquar->nb_cmd = 0;
	fquar->cargc = argc; 
	fquar->cargv = argv;
	fquar->cflag = flag;
	fquar->cmd_lst = NULL;
	fquar->sa = NULL;  
	fquar->sb = NULL;  
	fquar->arr = arr_to_sort(argc, argv);	
	quicksort(fquar->arr, 0, argc - 2);	
	fquar->nb_quarts = (argc - 1 < 250) ? 
		(argc - 1) / 11 - 1 : (argc - 1) / 28 - 1;
	fquar->quarts = find_quartiles(fquar->arr, argc - 1, fquar->nb_quarts); 
	return (fquar);
}

t_sort *init_basic(int argc, char **argv, int *flag)
{
	t_sort *basic;

	if ((basic = (t_sort *)malloc(sizeof(t_sort))) == 0)
		return (NULL);		
	basic->name = "Basic sort";
	basic->nb_cmd = 0;
	basic->cargc = argc; 
	basic->cargv = argv;
	basic->cflag = flag;
	basic->cmd_lst = NULL;
	basic->sa = NULL;  
	basic->sb = NULL;  
	return (basic);
}

t_sort  **init_sorts(int argc, char **argv, int *flag)
{
	t_sort **s;

	s = (t_sort **)malloc(sizeof(t_sort *) * 5);
	s[0] = init_basic(argc, argv, flag);
	s[1] = init_small(argc, argv, flag);
	s[2] = init_reverse(argc, argv, flag);
	s[4] = init_fquar(argc, argv, flag);

	return (s);
}

int free_all(t_sort **s)
{
	free(s[4]->quarts);
	free(s[4]->arr);
	free(s[1]->arr);
	free(s[0]);
	free(s[1]);
	free(s[2]);
	free(s[4]);
	free(s);
	return (1);
}


/************************* PS - Main  ***************************/

int main(int argc, char **argv)
{
	int flag[127];
	t_sort **s;

	if (argc == 1)
		return (1);
	if (error_arg(argc, argv))
	{
		ft_putstr("Error\n");
		return (1);
	}
	s = init_sorts(argc, argv, flag);
	launch_all_sorts(s);
	free_all(s);


	return (0);
}
