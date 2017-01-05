/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 15:20:43 by bduron            #+#    #+#             */
/*   Updated: 2017/01/05 16:17:50 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
//#include "libft.h"

int error_arg(int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc) 
	{
		if (ft_atoi(argv[i]) == 0 && (*argv[i] != '0' || 
					(*argv[i] == '-' && argv[i][1] != '0')))
			return (1);
		i++;
	}
	return (0); 
}	

int main(int argc, char **argv)
{
	if (error_arg(argc, argv))
		ft_putstr("Error\n");
	else 
		ft_putstr("Ok\n");


	return (0);
}

