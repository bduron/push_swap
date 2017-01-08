/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 15:20:43 by bduron            #+#    #+#             */
/*   Updated: 2017/01/06 16:46:27 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

/**************** Error handling ***********************/

int error_duplicate(int argc, char **argv)
{
	int i;
	int j;

	i = 1;
	while (i < argc)
	{
		j = i + 1;		 
		while (j < argc)
			if (ft_atoi(argv[i]) == ft_atoi(argv[j++]))
				return (1); 
		i++;
	}	
	return (0);
}

int error_arg(int argc, char **argv)
{
	int i;
	int j;

	i = 1;
	while (i < argc) 
	{
		j = 0;
		if (argv[i][j] == '-')
			j++;
		while (argv[i][j])
			if (ft_isdigit(argv[i][j++]) == 0)
				return (1); 
		if (j - (argv[i][0] == '-') > 10)
			return (1); 
		if (j - (argv[i][0] == '-') == 10)
			if (ft_atoi(argv[i]) > 2147483647 
					|| ft_atoi(argv[i]) < -2147483648)
				return (1); 
		i++;
	}
	if (error_duplicate(argc, argv))
		return (1);
	return (0); 
}	


/**************** Sorting Commands **********************/

void sort_sx(t_list **head)
{	
	t_list *tmp;

	if ((*head)->next == NULL)
	   return ;	
	tmp = *head;
	*head = tmp->next;
	tmp->next = (*head)->next;
	(*head)->next = tmp;
}

void sort_rx(t_list **head)
{
	t_list *tmp;
	t_list *last;
	
	if ((*head)->next == NULL)
	   return ;	
	tmp = *head; 		//1
	*head = tmp->next;  	//2
	tmp->next = NULL;	//3
	last = *head;		//4
	while (last->next != NULL) //5  //6 //SEGFAULT ICI 
		last = last->next;		
	last->next = tmp;
}	

void sort_rrx(t_list **head)
{
	t_list *tmp;
	t_list *last;
	
	if ((*head)->next == NULL)
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

void sort_px(t_list **head_a, t_list **head_b)
{
	t_list *tmp;

	if (*head_b == NULL)
		return ;

	tmp = (*head_b)->next;	
	(*head_b)->next = *head_a;
	*head_a = *head_b;
	*head_b = tmp;
}

void launch_sort(t_list **head_a, t_list **head_b, char *cmd)
{
	if (ft_strcmp(cmd, "sa") == 0)
		sort_sx(head_a);
	else if (ft_strcmp(cmd, "sb") == 0)
		sort_sx(head_b);
	else if (ft_strcmp(cmd, "ss") == 0)
	{
		sort_sx(head_a);
		sort_sx(head_b);
	}
	else if (ft_strcmp(cmd, "ra") == 0)
		sort_rx(head_a);
	else if (ft_strcmp(cmd, "rb") == 0)
		sort_rx(head_b);
	else if (ft_strcmp(cmd, "rr") == 0)
	{
		sort_rx(head_a);
		sort_rx(head_b);
	}
	else if (ft_strcmp(cmd, "rra") == 0)
		sort_rrx(head_a);
	else if (ft_strcmp(cmd, "rrb") == 0)
		sort_rrx(head_b);
	else if (ft_strcmp(cmd, "rrr") == 0)
	{
		sort_rrx(head_a);
		sort_rrx(head_b);
	}
	else if (ft_strcmp(cmd, "pa") == 0)
		sort_px(head_a, head_b);
	else if (ft_strcmp(cmd, "pb") == 0)
		sort_px(head_b, head_a);
}


/**************** Utils *********************/

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
	return (-min >= max) ? min : max;
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

void print_list(t_list *list)
{
	while (list) 	 
	{
		printf("%d\n", *(int *)(list->content));
		list = list->next;
	}	
}


void print_two(t_list *a, t_list *b, int size)
{
	size_t len_a;
	size_t len_b;
	size_t len_diff;
	char big_lst;
 
	len_a = lstlen(a);
	len_b = lstlen(b);
	big_lst = (len_a >= len_b) ? 'a' : 'b';
	len_diff = (big_lst == 'a') ? len_a - len_b : len_b - len_a;	
	printf("\n");
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
		printf(" |%*d|  |%*d|\n", size, *(int *)(a->content), size, *(int *)b->content);
		a = a->next;
		b = b->next;	
	}	
	printf(" (%*c)  (%*c) \n", size, 'A', size, 'B');
}


/**************** Main **********************/

t_list *create_stack(int argc, char **argv)
{
	t_list *head;
	int i;
	int val;
	
	i =  argc - 1;
	val = ft_atoi(argv[i--]);	
	head = ft_lstnew(&val, sizeof(int));
	while (i > 0)
	{
		val = ft_atoi(argv[i--]);	
		ft_lstadd(&head, ft_lstnew(&val, sizeof(int)));			
	}
	return (head);
}

int main(int argc, char **argv)
{
	t_list *stack_a;
	t_list *stack_b;

	if (argc == 1)
		return (1);
	if (error_arg(argc, argv))
		ft_putstr("Error\n");

	stack_a = create_stack(argc, argv);	
	stack_b = create_stack(argc, argv);
//	stack_b = NULL;
		
//	sort_sx(&stack_b);
//	sort_rrx(&stack_b);
//	sort_sx(&stack_b);
//	sort_px(&stack_a, &stack_b);

	launch_sort(&stack_a, &stack_b, "pb");
	launch_sort(&stack_a, &stack_b, "rrb");

	print_two(stack_a, stack_b, nb_digit(array_max_min(argc, argv)));

//	printf("\x1B[32m");
//	print_two(stack_a, stack_b, nb_digit(array_max_min(argc, argv)));
//	printf("\x1B[0m");
//	printf("\nmax = %d\n", array_max_min(argc, argv));
//	printf("\nnb digits = %d\n", nb_digit(array_max_min(argc, argv)));

	return (0);
}




/*

===============================
	head
         |	
1/	 1 --> 2 --> 3 --> NULL
	 |
	tmp
================================
	      head
               |	
2/	 1 --> 2 --> 3 --> NULL
	 |
	tmp
================================
	             head
                      |	
3/	 1 -->NULL    2 --> 3 --> NULL
	 |
	tmp
================================
	             head
                      |	
4/	 1 -->NULL    2 --> 3 --> NULL
	 |            |
	tmp          last     
================================
	             head
                      |	
5/	 1 -->NULL    2 --> 3 --> NULL // Segfault 
	 |            	    |
	tmp                last     
================================
	             head
                      |	
6/	              2 --> 3 --> 1 --> NULL
	              	    |     |
	                   last  tmp   
================================
*/
