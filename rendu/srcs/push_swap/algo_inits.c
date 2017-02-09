/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_inits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 14:08:40 by bduron            #+#    #+#             */
/*   Updated: 2017/02/08 16:27:03 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_sort	**init_sorts(int argc, char **argv, int *flag)
{
	t_sort **s;

	s = (t_sort **)malloc(sizeof(t_sort *) * 5);
	s[0] = init_basic(argc, argv, flag);
	if (argc - 1 < 30)
	{
		s[1] = init_small(argc, argv, flag);
		s[2] = init_reverse(argc, argv, flag);
	}
	if (argc - 1 >= 30) 
		s[4] = init_fquar(argc, argv, flag);
	return (s);
}

t_sort	*init_basic(int argc, char **argv, int *flag)
{
	t_sort *basic;

	if ((basic = (t_sort *)malloc(sizeof(t_sort))) == 0)
		return (NULL);
	basic->name = "Basic sort";
	basic->nb_cmd = 0;
	basic->cargc = argc;
	basic->cargv = argv;
	basic->cflag = flag;
	basic->cmd_lst = NULL;
	basic->sa = NULL;
	basic->sb = NULL;
	return (basic);
}

t_sort	*init_fquar(int argc, char **argv, int *flag)
{
	t_sort *fquar;

	if ((fquar = (t_sort *)malloc(sizeof(t_sort))) == 0)
		return (NULL);
	fquar->name = "Find quartiles sort";
	fquar->nb_cmd = 0;
	fquar->cargc = argc;
	fquar->cargv = argv;
	fquar->cflag = flag;
	fquar->cmd_lst = NULL;
	fquar->sa = NULL;
	fquar->sb = NULL;
	fquar->arr = arr_to_sort(argc, argv);
	quicksort(fquar->arr, 0, argc - 2);
	fquar->nb_quarts = (argc - 1 < 250) ?
		(argc - 1) / 11 /*- 1*/ : (argc - 1) / 28 /*- 1*/;
	fquar->quarts = find_quartiles(fquar->arr, argc - 1, fquar->nb_quarts);
	return (fquar);
}

t_sort	*init_reverse(int argc, char **argv, int *flag)
{
	t_sort *reverse;

	if ((reverse = (t_sort *)malloc(sizeof(t_sort))) == 0)
		return (NULL);
	reverse->name = "Small sort";
	reverse->nb_cmd = 0;
	reverse->cargc = argc;
	reverse->cargv = argv;
	reverse->cflag = flag;
	reverse->cmd_lst = NULL;
	reverse->sa = NULL;
	reverse->sb = NULL;
	return (reverse);
}

t_sort	*init_small(int argc, char **argv, int *flag)
{
	t_sort *small;

	if ((small = (t_sort *)malloc(sizeof(t_sort))) == 0)
		return (NULL);
	small->name = "Small sort";
	small->nb_cmd = 0;
	small->cargc = argc;
	small->cargv = argv;
	small->cflag = flag;
	small->cmd_lst = NULL;
	small->sa = NULL;
	small->sb = NULL;
	small->arr = arr_to_sort(argc, argv);
	quicksort(small->arr, 0, argc - 2);
	return (small);
}
