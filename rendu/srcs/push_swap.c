/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 08:50:53 by bduron            #+#    #+#             */
/*   Updated: 2017/01/11 17:24:23 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// `ruby -e "puts (1..100).to_a.shuffle.join('  ')"`

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


/************************* PS  -  launch sorting algorithms wrapper ***************************/

void launch_wrapper(t_sort *s, char *cmd, int print)
{
	launch_sort(&s->sa, &s->sb, cmd);
	s->nb_cmd++;	
	if (print)
		print_two(s->sa, s->sb, nb_digit(array_max_min(s->cargc, s->cargv)));  
	ft_lstaddback(&s->cmd_lst, ft_lstnew(cmd, sizeof(char) * 4));			
}

void print_wrap(t_sort *s)
{
	print_two(s->sa, s->sb, nb_digit(array_max_min(s->cargc, s->cargv)));  
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


int find_next(t_list *s, int median)
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
		if (first == -1 && *(int *)s->content <= median)
			first = *(int *)s->content;
		if (first == -1)	
			first_i++;
		if (*(int *)s->content <= median)
		{
			last = *(int *)s->content;
			last_i = i;
		}
		i++;
		s = s->next;		
	}		
	// IF last && first == -1 ? 
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

int find_min(t_list *s)
{	
	int min;
	
	if (!s || !s->next)
		return (-1);
	min = *(int *)s->content;
	while (s)
	{
		min = (*(int *)s->content < min) ? *(int *)s->content : min;
		s = s->next;
	}	
	return (min);
}

int medians_rem(t_list *s, int n)
{
	if (!s)
		return (-1);	
	while (s)
	{
		if (*(int *)s->content <= n)
			return (1);
		s = s->next;	
	}	
	return (0);
}

void launch_fquar(t_sort *s)
{	
	int i;
	int max;
	int best_cmd;
	int next;

	s->sa = create_stack(s->cargc, s->cargv);	
	s->sb = NULL;

	print_two(s->sa, s->sb, nb_digit(array_max_min(s->cargc, s->cargv))); // 
	
//	printf("\nQuartiles\n");
//	i = 0;
//	while (s->quarts[i] != -1)
//		printf("%d ", s->quarts[i++]);
//////////// FIND NEAREST
//	i = 0;
//	int next = find_next(s->sa, s->quarts[i]);
//	printf("\nThe nearest number below the median %d is %d.\n", s->quarts[i], next);

	i = 0;
	while (s->sa)
	{
		if (*(int *)s->sa->content <= s->quarts[i])
    		launch_wrapper(s, "pb", 0);
		if (medians_rem(s->sa, s->quarts[i]) == 0)
			i++; 
		next = find_next(s->sa, s->quarts[i]);	
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
		
			
	print_two(s->sa, s->sb, nb_digit(array_max_min(s->cargc, s->cargv)));
	printf("%s : %zu operations for %d values\n", s->name, s->nb_cmd, s->cargc - 1);
//	while (s->cmd_lst)
//	{
//		printf("%s\n", (char *)s->cmd_lst->content);	
//		s->cmd_lst = s->cmd_lst->next; 	
//	}	
}

void launch_fmed(t_sort *s)
{	
	int i;
	int max;
	int best_cmd;
	int next;

	s->sa = create_stack(s->cargc, s->cargv);	
	s->sb = NULL;

	print_two(s->sa, s->sb, nb_digit(array_max_min(s->cargc, s->cargv))); // 
	
//	printf("\n");
//	i = 0;
//	while (i < s->cargc - 1)
//		printf("%d ", s->arr[i++]);
//	printf("\nlog(16) = %d\n", find_log(16));
//	i = 0;
//	while (s->medians[i] != -1)
//		printf("%d ", s->medians[i++]);
//////////// FIND NEAREST
//	i = 0;
//	int next = find_next(s->sa, s->medians[i]);
//	printf("The nearest number below the median %d is %d.\n", s->medians[i], next);



	i = 0;
	while (s->medians[i] != -1)
	{
		if (*(int *)s->sa->content <= s->medians[i])
    		launch_wrapper(s, "pb", 1);
		if (medians_rem(s->sa, s->medians[i]) == 0)
			i++; 
		next = find_next(s->sa, s->medians[i]);	
      	best_cmd = rrx_or_rx(s->sa, next);
      	if (best_cmd == 0)
      		while (*(int *)s->sa->content != next)
      			launch_wrapper(s, "rra", 1);
      	else if (best_cmd == 1)
      		while (*(int *)s->sa->content != next)
      			launch_wrapper(s, "ra", 1);
	}
    launch_wrapper(s, "pb", 1);
	while (s->sb != NULL)
	{
		max = find_max(s->sb);	
      	best_cmd = rrx_or_rx(s->sb, max);
      	if (best_cmd == 0)
      		while (*(int *)s->sb->content != max)
      			launch_wrapper(s, "rrb", 1);
      	else if (best_cmd == 1)
      		while (*(int *)s->sb->content != max)
      			launch_wrapper(s, "rb", 1);
		launch_wrapper(s, "pa", 1);
	}
		
//	min = find_min(s->sa);
//	printf("\nMin = %d\n", min);
//	if (rrx_or_rx(s->sa, min) == 0)
//		printf("Best command to reach %d is RRX\n", min);
//	else 	
//		printf("Best command to reach %d is RX\n", min);

			
	print_two(s->sa, s->sb, nb_digit(array_max_min(s->cargc, s->cargv)));
	printf("%s : %zu operations for %d values\n", s->name, s->nb_cmd, s->cargc - 1);
	while (s->cmd_lst)
	{
		printf("%s\n", (char *)s->cmd_lst->content);	
		s->cmd_lst = s->cmd_lst->next; 	
	}	
}

void launch_fmin(t_sort *s)
{	
	int min;
	int best_cmd;

	s->sa = create_stack(s->cargc, s->cargv);	
	s->sb = NULL;

////	print_two(s->sa, s->sb, nb_digit(array_max_min(s->cargc, s->cargv))); // 
	while (s->sa != NULL)
	{
		min = find_min(s->sa);	
      	best_cmd = rrx_or_rx(s->sa, min);
      	if (best_cmd == 0)
      		while (*(int *)s->sa->content != min)
      			launch_wrapper(s, "rra", 0);
      	else if (best_cmd == 1)
      		while (*(int *)s->sa->content != min)
      			launch_wrapper(s, "ra", 0);
		launch_wrapper(s, "pb", 0);
	}
	while (s->sb != NULL)	
		launch_wrapper(s, "pa", 0);
			
////	print_two(s->sa, s->sb, nb_digit(array_max_min(s->cargc, s->cargv)));
	printf("%s : %zu operations for %d values\n", s->name, s->nb_cmd, s->cargc - 1);
}

void launch_basic(t_sort *s)
{
	s->sa = create_stack(s->cargc, s->cargv);	
	s->sb = NULL;

	while (!is_sorted(s->sa, s->sb))
	{	
		while (s->sa != NULL)	
		{
			if (s->sb && s->sb->next)
				if (*(int *)s->sb->content < *(int *)s->sb->next->content)	
					launch_wrapper(s, "sb", 0);
			launch_wrapper(s, "pb", 0);
		}
		while (s->sb != NULL)	
		{
			if (s->sb->next)
				if (*(int *)s->sb->content < *(int *)s->sb->next->content)	
					launch_wrapper(s, "sb", 0);
			launch_wrapper(s, "pa", 0);
		}
	}
////	print_wrap(s);
	printf("%s : %zu operations for %d values\n", s->name, s->nb_cmd, s->cargc - 1);
//	while (s->cmd_lst)
//	{
//		printf("%s\n", (char *)s->cmd_lst->content);	
//		s->cmd_lst = s->cmd_lst->next; 	
//	}	
}


void launch_all_sorts(t_sort **s)
{
//	launch_basic(s[0]);
//	launch_quicksort(s[1]);
//	launch_fmin(s[2]);
//	launch_fmed(s[3]);
	launch_fquar(s[4]);
	//launch_basic(s[2]);
	//launch_basic(s[3]);
	//launch_basic(s[4]);



}

/********* generate array, quicksort it, find median ************/

int find_log(int n)
{
	int i;

	i = 0;
	while (n /= 2)
		i++;	
	return (i);
}

int *find_quartiles(int *arr, int size, int nb)
{
	int *quartiles;
	int i;	
	int j;

	quartiles = (int *)malloc(sizeof(int) * nb + 2);	
	i = 0;
	j = 0;
	while (i < size && j < nb)
	{
		i = i + size / (nb + 1);
		quartiles[j] = arr[i];
		j++;
	}	 	
	quartiles[j++] = arr[size - 1];	
	quartiles[j] = -1;	
	return (quartiles);
}

int *find_medians(int *arr, int size)
{
	int *medians;
	int i;	
	int len;

	medians = (int *)malloc(sizeof(int) * find_log(size) + 1);	

	i = 0;
	len = size;
	while (size /= 2)
		medians[i++] = arr[len - size - 1];
		 	
	medians[i] = -1;	

	return (medians);
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
	fquar->quarts = find_quartiles(fquar->arr, argc - 1, 40); // rendre nb_quartiles variable 
	return (fquar);
}

t_sort *init_fmed(int argc, char **argv, int *flag)
{
	t_sort *fmed;

	if ((fmed = (t_sort *)malloc(sizeof(t_sort))) == 0)
		return (NULL);		
	fmed->name = "Find medians sort";
	fmed->nb_cmd = 0;
	fmed->cargc = argc; 
	fmed->cargv = argv;
	fmed->cflag = flag;
	fmed->cmd_lst = NULL;
	fmed->sa = NULL;  
	fmed->sb = NULL;  
	fmed->arr = arr_to_sort(argc, argv);	
	quicksort(fmed->arr, 0, argc - 2);	
	fmed->medians = find_medians(fmed->arr, argc - 1);
	return (fmed);
}

t_sort *init_fmin(int argc, char **argv, int *flag)
{
	t_sort *fmin;

	if ((fmin = (t_sort *)malloc(sizeof(t_sort))) == 0)
		return (NULL);		
	fmin->name = "Find min sort";
	fmin->nb_cmd = 0;
	fmin->cargc = argc; 
	fmin->cargv = argv;
	fmin->cflag = flag;
	fmin->cmd_lst = NULL;
	fmin->sa = NULL;  
	fmin->sb = NULL;  
	return (fmin);
}

t_sort *init_quicksort(int argc, char **argv, int *flag)
{
	t_sort *quicksort;

	if ((quicksort = (t_sort *)malloc(sizeof(t_sort))) == 0)
		return (NULL);		
	quicksort->name = "Quicksort";
	quicksort->nb_cmd = 0;
	quicksort->cargc = argc; 
	quicksort->cargv = argv;
	quicksort->cflag = flag;
	quicksort->cmd_lst = NULL;
	quicksort->sa = NULL;  
	quicksort->sb = NULL;  
	return (quicksort);
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
	s[1] = init_quicksort(argc, argv, flag);
	s[2] = init_fmin(argc, argv, flag);
	s[3] = init_fmed(argc, argv, flag);
	s[4] = init_fquar(argc, argv, flag);
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
