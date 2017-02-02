/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 15:20:43 by bduron            #+#    #+#             */
/*   Updated: 2017/02/02 14:01:19 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	for (;;) // REMOVE
		;
	return (0);
}
