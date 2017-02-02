/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 14:54:52 by bduron            #+#    #+#             */
/*   Updated: 2017/02/02 10:51:44 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h> // TO REMOVE

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include "get_next_line.h"

typedef struct s_sort
{
	char 	*name;
	size_t 	nb_cmd;
	t_list  *sa;
	t_list  *sb;
	t_list  *cmd_lst;
	t_list  *srev;
	int 	cargc;
	char 	**cargv;
	int 	*cflag;
	int 	*arr;
	int 	*medians;
	int 	*quarts;
	int 	nb_quarts;
}				t_sort;

void error_exit(void);
int error_duplicate(int argc, char **argv);
int error_arg(int argc, char **argv);

void sort_sx(t_list **head);
void sort_rx(t_list **head);
void sort_rrx(t_list **head);
void sort_px(t_list **head_a, t_list **head_b);
void launch_sort(t_list **head_a, t_list **head_b, char *cmd);
void launch_sort_next(t_list **head_a, t_list **head_b, char *cmd);

int array_max_min(int argc, char **argv);
int nb_digit(int n);
size_t lstlen(t_list *list);
void print_two(t_list *a, t_list *b, int size);

t_list *create_stack(int argc, char **argv);
int is_sorted(t_list *stack_a, t_list *stack_b);
void    ft_lstdel_simple(t_list **alst);

#endif
