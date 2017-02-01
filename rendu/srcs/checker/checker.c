/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 15:20:43 by bduron            #+#    #+#             */
/*   Updated: 2017/02/01 16:38:25 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#include <stdio.h> // TO DEL

void ft_usleep(int time)
{
	int i;
	int j;

	i = 0;
	while (i++ < time)
	{	
		j = 0;
		while (j++ < time)
			;
	}
}

void ft_strsplitdel(char **split, int size)
{
	int i;
//	char **tab = *split;

//	if (!split)
//		return ;
	i = 0;
	while (i < size)
		free(split[i++]);                        
	free(split);
//	*split = NULL;
}

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

int get_cmd(char **cmd_list)
{
	int nb_cmd;

	nb_cmd = 0;	
	while (get_next_line(0, &cmd_list[nb_cmd]))
	{
		if (is_cmd(cmd_list[nb_cmd]) == 0)
		{
			printf("Error\n");
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
			if (argv[1][i] == 'v' || argv[1][i] == 'c' 
					|| argv[1][i] == 'i' || argv[1][i] == 'n')
				flag[(int)argv[1][i]]++;
			else 
			{
				ft_putstr("usage: checker [-vci] number list\n");
				ft_putstr("  -v verbose mode\n  -c result highlighting\n");
				ft_putstr("  -i interactive mode\n");
				ft_putstr("  -n display operation count\n");
				exit(1);
			}
			i++;
		}
		*argc -= 1;
		return (argv + 1);
	}	
	flag[0] = *argc - 1;
	return (argv);
}

void sort_print_stack(t_list **stack_a, t_list **stack_b,
		char **argv, int *flag)
{
//	char *cmd_list[64000];
	char **cmd_list;
	int nb_cmd;
	int i;

	cmd_list = (char **)malloc(sizeof(char *) * 6400);
	nb_cmd = get_cmd(cmd_list);	
	i = 0;
	while (i < nb_cmd)
	{
		launch_sort(stack_a, stack_b, cmd_list[i++]);
		if (flag['v'])
			print_two(*stack_a, *stack_b, nb_digit(array_max_min(*flag, argv)));
		else if (flag['i'])
		{
			ft_usleep(3500);
			printf("\33[2J");
			print_two(*stack_a, *stack_b, nb_digit(array_max_min(*flag, argv)));
			printf(" [%s]\n", cmd_list[i - 1]);
		}
	}	
	if (flag['c'])
	{
		if (flag['i'])
			printf("\33[2J");
		printf("\x1B[32m");
		print_two(*stack_a, *stack_b, nb_digit(array_max_min(flag[0], argv)));
		printf("\x1B[0m");
	}	
	if (flag['n'])
		printf(" [" "\x1B[32m" "%d" "\x1B[0m" " operations for " "\x1B[32m" "%d" "\x1B[0m" " values]\n\n", nb_cmd, flag[0] - 1);

	ft_strsplitdel(cmd_list, nb_cmd);
}

int has_space(char *s)
{
	if (!s)
		return (0);
	while (*s)
		if (*s++ == ' ')
			return (1);	
	return (0);
}
// Split white space, regulariser argc, assouplir la gestion d;erreur 

char **normalize_argv(char **argv, int *argc, int *is_normalized)
{
	int i;
	int j;
	char *last;
	char *current;


	i = 0;
	//	printf("Argc before : %d\n", *argc); //	
	if (*argc == 2 && has_space(argv[1])) 
	{
		argv = ft_strsplit(argv[1], ' ');
		while (argv[i])
			//	printf("%s ", argv[i++]);	
			i++;
		*argc = i + 1;

		//	for (i = 0; i < *argc - 1; i++)
		//		printf("%s ", argv[i]);

		j = 0;
		last = ft_strdup("./checker");		
		while (j < i)
		{
			current = argv[j];			
			argv[j] = last;
			last = current;
			j++;
		}
		argv[j] = last;
		*is_normalized = 1;
		//	[3][2][1][NULL]
		//	[n][3][2][1]
		//	 0  1  2  3					
	}

	//	for (i = 0; i < *argc; i++)
	//		printf("%s ", argv[i]);

	//	printf("Argc after : %d\n", *argc); //	
	return (argv);
}

/** OK cleaner, checker interference avec les flags d'options **/


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


//LEAKS 
//int main(void)
//{
//	int i;
//	int j;
//	char **list;
//
//	list = (char **)malloc(sizeof(char *) * 6400);
//
//	i = 0;	
//	while (get_next_line(0, &list[i]))
//		i++;
//	
//	j = 0;
//	while (j < i)
//		printf("%s\n", list[j++]);
//
//	ft_strsplitdel(list, 702);	
////	list = NULL;
//	for (;;)
//		;
//	return (1);
//}

int main(int argc, char **argv)
{
	t_list *stack_a;
	t_list *stack_b;
	int flag[127];

	if (argc == 1)
		return (1);
	argv = get_flag(&argc, argv, flag);
	if (error_arg(argc, argv))
	{
		ft_putstr("Error\n");
		return (1);
	}
	stack_a = create_stack(argc, argv);	
	stack_b = NULL;
	flag[0] = argc;
	sort_print_stack(&stack_a, &stack_b, argv, flag);
	is_sorted(stack_a, stack_b) ? printf("OK\n") : printf("KO\n");

	ft_lstdel_simple(&stack_a);

	for (;;)
		;
	return (0);
}
