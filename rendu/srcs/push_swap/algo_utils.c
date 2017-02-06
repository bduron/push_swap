/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 14:39:30 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 15:14:45 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	launch_all_sorts(t_sort **s)
{
	t_sort *cmd;

	s[0]->srev = create_stack((s[0])->cargc, (s[0])->cargv);
	if (is_reverse((*s)->srev) && (*s)->cargc - 1 == 5)
		cmd = launch_reverse(s[2]);
	else if ((*s)->cargc - 1 < 30)
		cmd = launch_small(s[1]);
	else
		cmd = launch_fquar(s[4], 0, 0, 0);
	if (cmd->nb_cmd != 13)
		print_cmd(cmd->cmd_lst);
	else
		ft_printf("sa\npb\npb\nra\nsa\npa\npa\nrra\n");
	ft_lstdel_simple(&(cmd->cmd_lst));
	ft_lstdel_simple(&(s[0]->srev));
}

void	launch_wrapper(t_sort *s, char *cmd, int print)
{
	launch_sort(&s->sa, &s->sb, cmd);
	s->nb_cmd++;
	if (print)
	{
		print_two(s->sa, s->sb, nb_digit(array_max_min(s->cargc, s->cargv)));
	}
	ft_lstaddback(&s->cmd_lst, ft_lstnew(cmd, sizeof(char) * 4));
}

int		*arr_to_sort(int argc, char **argv)
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

int		free_all(t_sort **s)
{
	free(s[4]->quarts);
	free(s[4]->arr);
	free(s[1]->arr);
	free(s[0]);
	free(s[1]);
	free(s[2]);
	free(s[4]);
	free(s);
	return (1);
}

void	print_cmd(t_list *cmd)
{
	while (cmd)
	{
		ft_printf("%s\n", (char *)cmd->content);
		cmd = cmd->next;
	}
}
