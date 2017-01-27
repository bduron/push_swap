/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 14:54:52 by bduron            #+#    #+#             */
/*   Updated: 2017/01/27 13:05:27 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

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

int nb_digit(int n);
int find_log(int n);

#endif
