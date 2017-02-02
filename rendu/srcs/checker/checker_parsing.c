/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 12:24:20 by bduron            #+#    #+#             */
/*   Updated: 2017/02/02 12:34:22 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
				ft_putstr("usage: checker [-vcin] number list\n");
				ft_putstr("  -v verbose mode\n  -c highlight result\n");
				ft_putstr("  -i interactive mode\n  -n display op count\n");
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
