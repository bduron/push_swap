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
	else  						// TO DEL
		ft_putstr("Ok\n"); 		// TO DEL

	stack_a = create_stack(argc, argv);	
	stack_b = ft_lstnew(0, 0);
		
	sort_sx(&stack_a);
	sort_sx(&stack_b);


	while (stack_a) 				// PRINT LIST 
	{
		printf("%d\n", *(int *)(stack_a->content));
		stack_a = stack_a->next;
	}	

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
