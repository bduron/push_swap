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

int error_duplicate(int argc, char **argv)
{
	int i;
	int j;
	
	i = 1;
	while (i < argc)
	{
		j = i + 1;		 
		while (j < argc)
			if (ft_atoi(argv[i]) == ft_atoi(argv[j++]))
				return (1); 
		i++;
	}	
	return (0);
}

int error_arg(int argc, char **argv)
{
	int i;
	int j;

	i = 1;
	while (i < argc) 
	{
		j = 0;
		if (argv[i][j] == '-')
			j++;
		while (argv[i][j])
			if (ft_isdigit(argv[i][j++]) == 0)
				return (1); 
		if (j - (argv[i][0] == '-') > 10)
			return (1); 
		if (j - (argv[i][0] == '-') == 10)
			if (ft_atoi(argv[i]) > 2147483647 
			|| ft_atoi(argv[i]) < -2147483648)
				return (1); 
		i++;
	}
	if (error_duplicate(argc, argv))
		return (1);
	return (0); 
}	

int main(int argc, char **argv)
{
	if (error_arg(argc, argv))
		ft_putstr("Error\n");
	else 
		ft_putstr("Ok\n"); // TO DEL
	

	return (0);
}

