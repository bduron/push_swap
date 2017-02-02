/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 14:54:52 by bduron            #+#    #+#             */
/*   Updated: 2017/02/02 17:37:13 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h> // TO REMOVE

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include "libftprintf.h"
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

int is_cmd(char *cmd);
int get_cmd(char **cmd_list);
char **get_flag(int *argc, char **argv, int *flag);

void ft_usleep(int time);
void ft_strsplitdel(char **split, int size);
void option_display(t_list **stack_a, t_list **stack_b, char **argv, int *flag);
void sort_print_stack(t_list **stack_a, t_list **stack_b, char **argv, int *flag);
void option_n(int *flag, int nb_cmd);

int is_near_sorted(t_sort *s);
int is_reverse(t_list *stack);
int rrx_or_rx(t_list *s, int min);
int find_max(t_list *s);

t_sort  **init_sorts(int argc, char **argv, int *flag);
t_sort *init_basic(int argc, char **argv, int *flag);
t_sort *init_fquar(int argc, char **argv, int *flag);
t_sort *init_reverse(int argc, char **argv, int *flag);
t_sort *init_small(int argc, char **argv, int *flag);

void swap(int *a, int *b);
int partionning(int *arr, int start, int end);
int *quicksort(int *arr, int start, int end);

int *find_quartiles(int *arr, int size, int nb);
int quarts_rem(t_list *s, int lower, int upper);
int find_quartile(t_list *s, int lower, int upper, int i);
t_sort *launch_fquar(t_sort *s, int max, int best_cmd, int next);
void empty_stack_a(t_sort *s, int best_cmd, int next);

void launch_wrapper(t_sort *s, char *cmd, int print);
int *arr_to_sort(int argc, char **argv);
int free_all(t_sort **s);
void launch_all_sorts(t_sort **s);
void print_cmd(t_list *cmd);

int find_unsorted(t_sort *s, int last, int i);
t_sort *launch_reverse(t_sort *s);
t_sort *launch_small(t_sort *s);
void launch_small_next(t_sort *s, int min, int best_cmd);


#endif
