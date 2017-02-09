/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 15:20:43 by bduron            #+#    #+#             */
/*   Updated: 2017/02/06 11:59:16 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int		main(int argc, char **argv)
{
	t_list	*stack_a;
	t_list	*stack_b;
	int		flag[127];

	if (argc == 1)
		return (1);
	argv = get_flag(&argc, argv, flag);
	if (error_arg(argc, argv))
		error_exit();
	stack_a = create_stack(argc, argv);
	stack_b = NULL;
	flag[0] = argc;
	sort_print_stack(&stack_a, &stack_b, argv, flag);
	is_sorted(stack_a, stack_b) ? ft_printf("OK\n") : ft_printf("KO\n");
	ft_lstdel_simple(&stack_a);
	ft_lstdel_simple(&stack_b);
	return (0);
}
