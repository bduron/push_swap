/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 15:20:43 by bduron            #+#    #+#             */
/*   Updated: 2017/02/02 10:51:50 by bduron           ###   ########.fr       */
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



/**************** Main **********************/


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
