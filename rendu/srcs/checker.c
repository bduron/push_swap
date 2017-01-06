/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 15:20:43 by bduron            #+#    #+#             */
/*   Updated: 2017/01/06 16:45:15 by bduron           ###   ########.fr       */
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
	tmp = *head;
	*head = tmp->next; 
	tmp->next = NULL;
	last = *head;	
	while (last->next != NULL)
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


/**************** Main **********************/

int main(int argc, char **argv)
{
	t_list *head;
	int val;
	int i;

	if (argc == 1)
		return (1);
	if (error_arg(argc, argv))
		ft_putstr("Error\n");
	else  						// TO DEL
		ft_putstr("Ok\n"); 		// TO DEL

	i =  argc - 1;
	while (i > 0)
	{
		val = ft_atoi(argv[i--]);	
		ft_lstadd(&head, ft_lstnew(&val, sizeof(int)));			
	}

	sort_rrx(&head);


	while (head) 				// PRINT LIST 
	{
		printf("%d\n", *(int *)(head->content));
		head = head->next;
	}	

	return (0);
}

