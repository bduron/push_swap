/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 08:50:53 by bduron            #+#    #+#             */
/*   Updated: 2017/01/11 15:56:03 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#include <stdio.h>

#define sort(x) do { printf("\n %s %C \n", #x, L'↴'); \
	launch_sort(&stack_a, &stack_b, x); \
	print_two(stack_a, stack_b, nb_digit(array_max_min(argc, argv)));} while (0)


/**************** Error handling ***********************/

void error_exit(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

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

int is_cmd(char *cmd)
{
	int i;

	i = 0;	
	i += (ft_strcmp(cmd, "sa") == 0) ? 1 : 0;
	i += (ft_strcmp(cmd, "sb")  == 0) ? 1 : 0;
	i += (ft_strcmp(cmd, "ss")  == 0) ? 1 : 0;
	i += (ft_strcmp(cmd, "ra")  == 0) ? 1 : 0;
	i += (ft_strcmp(cmd, "rb")  == 0) ? 1 : 0;
	i += (ft_strcmp(cmd, "rr")  == 0) ? 1 : 0;
	i += (ft_strcmp(cmd, "rra") == 0) ? 1 : 0;
	i += (ft_strcmp(cmd, "rrb") == 0) ? 1 : 0;
	i += (ft_strcmp(cmd, "rrr") == 0) ? 1 : 0;
	i += (ft_strcmp(cmd, "pa")  == 0) ? 1 : 0;
	i += (ft_strcmp(cmd, "pb")  == 0) ? 1 : 0;
	return (i) ? 1 : 0;
}

void sort_sx(t_list **head)
{	
	t_list *tmp;

	if (!*head || (*head)->next == NULL)
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

	if (!*head || (*head)->next == NULL)
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


/**************** Main  Checker **********************/

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

int get_cmd(char **cmd_list)     // USELESS
{
	int nb_cmd;

	nb_cmd = 0;	
	while (get_next_line(0, &cmd_list[nb_cmd]))
	{
		if (is_cmd(cmd_list[nb_cmd]) == 0)
		{
			printf("KO\n");
			exit(0);
		}	
		nb_cmd++;
	}
	return (nb_cmd);
}

int is_sorted(t_list *stack_a, t_list *stack_b)
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

char **get_flag(int *argc, char **argv, int *flag)
{
	int  i;

	ft_bzero(flag, sizeof(int) * 127); 
	if (argv[1][0] == '-')
	{
		i = 1;
		while (argv[1][i]) 
		{		
			if (argv[1][i] == 'v' || argv[1][i] == 'c')
				flag[(int)argv[1][i]]++;
			else 
			{
				ft_putstr("usage: checker [-vc] number list\n");
				ft_putstr("  -v verbose mode\n  -c result highlighting\n");
				exit(1);
			}
			i++;
		}
		*argc -= 1;
		return (argv + 1);
	}	
	return (argv);
}

void sort_print_stack(t_list **stack_a, t_list **stack_b,    // USELESS
		char **argv, int *flag)
{
	char **cmd_list;
	int nb_cmd;
	int i;

	cmd_list = (char **)malloc(sizeof(char *) * 4096);
	nb_cmd = get_cmd(cmd_list);	
	i = 0;
	while (i < nb_cmd)
	{
		launch_sort(stack_a, stack_b, cmd_list[i++]);
		if (flag['v'])
			print_two(*stack_a, *stack_b, nb_digit(array_max_min(*flag, argv)));
	}	
	if (flag['c'])
	{
		printf("\x1B[32m");
		print_two(*stack_a, *stack_b, nb_digit(array_max_min(flag[0], argv)));
		printf("\x1B[0m");
	}	
	free(cmd_list);
}


/************************* PS  -  launch sorting algorithms ***************************/


void launch_basic(t_sort *s)
{
  	s->stack_a = create_stack(s->cargc, s->cargv);	
  	s->stack_b = NULL;
	
	print_two(s->stack_a, s->stack_b, nb_digit(array_max_min(s->cargc, s->cargv)));
	while (s->stack_a != NULL)	
	{
		if (s->stack_b && s->stack_b->next)
			if (*(int *)s->stack_b->content < *(int *)s->stack_b->next->content)	
				launch_sort(&s->stack_a, &s->stack_b, "sb");
		launch_sort(&s->stack_a, &s->stack_b, "pb");
	}
	print_two(s->stack_a, s->stack_b, nb_digit(array_max_min(s->cargc, s->cargv)));
	while (s->stack_b != NULL)	
	{
		if (s->stack_b->next)
			if (*(int *)s->stack_b->content < *(int *)s->stack_b->next->content)	
				launch_sort(&s->stack_a, &s->stack_b, "sb");
		launch_sort(&s->stack_a, &s->stack_b, "pa");
	}
	print_two(s->stack_a, s->stack_b, nb_digit(array_max_min(s->cargc, s->cargv)));
}


void launch_all_sorts(t_sort **s)
{
	launch_basic(s[0]);
	//launch_basic(s[1]);
	//launch_basic(s[2]);
	//launch_basic(s[3]);
	//launch_basic(s[4]);



}



/************************* PS  -  init_sorts  ***************************/

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
	basic->stack_a = NULL;  
	basic->stack_b = NULL;  
	return (basic);
}

t_sort  **init_sorts(int argc, char **argv, int *flag)
{
	t_sort **s;

	s = (t_sort **)malloc(sizeof(t_sort *) * 5);
	s[0] = init_basic(argc, argv, flag);
	//init_basic(s, argv, argc, flag);
	//init_basic(s, argv, argc, flag);
	//init_basic(s, argv, argc, flag);
	//init_basic(s, argv, argc, flag);

	return (s);
}


/************************* PS - Main  ***************************/

int main(int argc, char **argv)
{
	int flag[127];
	t_sort **s;

	if (argc == 1)
		return (1);
	//	argv = get_flag(&argc, argv, flag);  // ARG ? 
	if (error_arg(argc, argv))
	{
		ft_putstr("Error\n");
		return (1);
	}
	s = init_sorts(argc, argv, flag);
	launch_all_sorts(s);
///	print_winner(s);	

	return (0);
}













//int main(int argc, char **argv)
//{
//	t_list *stack_a;
//	t_list *stack_b;
//	int flag[127];
//
//	if (argc == 1)
//		return (1);
//	argv = get_flag(&argc, argv, flag);
//	if (error_arg(argc, argv))
//	{
//		ft_putstr("Error\n");
//		return (1);
//	}
//	stack_a = create_stack(argc, argv);	
//	stack_b = NULL;
//	flag[0] = argc;
//	sort_print_stack(&stack_a, &stack_b, argv, flag);
//	is_sorted(stack_a, stack_b) ? printf("OK\n") : printf("KO\n");
//
//	return (0);
//}
