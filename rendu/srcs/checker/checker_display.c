/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 12:36:21 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 11:37:57 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h" 

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
	i = 0;
	while (i < size)
		free(split[i++]);
	free(split);
}

void option_n(int *flag, int nb_cmd)
{
	if (flag['n'])
		ft_printf(" [" "\x1B[32m" "%d" "\x1B[0m" " operations for " 
				"\x1B[32m" "%d" "\x1B[0m" " values]\n\n", nb_cmd, flag[0] - 1);
}

void option_display(t_list **stack_a, t_list **stack_b, char **argv, int *flag)
{
	if (flag['c'])
	{
		if (flag['i'])
			ft_printf("\33[2J");
		ft_printf("\x1B[32m");
		print_two(*stack_a, *stack_b, nb_digit(array_max_min(flag[0], argv)));
		ft_printf("\x1B[0m");
	}
}

void sort_print_stack(t_list **stack_a, t_list **stack_b,
		char **argv, int *flag)
{
	char **cmd_list;
	int nb_cmd;
	int i;

	cmd_list = (char **)malloc(sizeof(char *) * 64000);
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
			ft_printf("\33[2J");
			print_two(*stack_a, *stack_b, nb_digit(array_max_min(*flag, argv)));
			ft_printf(" [%s]\n", cmd_list[i - 1]);
		}
	}
	option_display(stack_a, stack_b, argv, flag);
    option_n(flag, nb_cmd);
	ft_strsplitdel(cmd_list, nb_cmd);
}	
