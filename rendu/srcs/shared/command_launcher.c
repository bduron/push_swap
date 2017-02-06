/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_launcher.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 10:08:04 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 12:07:58 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	launch_sort_next(t_list **head_a, t_list **head_b, char *cmd)
{
	if (ft_strcmp(cmd, "rr") == 0)
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

void	launch_sort(t_list **head_a, t_list **head_b, char *cmd)
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
	else
		launch_sort_next(head_a, head_b, cmd);
}
