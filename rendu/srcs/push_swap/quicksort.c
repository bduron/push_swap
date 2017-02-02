/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 14:15:36 by bduron            #+#    #+#             */
/*   Updated: 2017/02/02 14:16:50 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void swap(int *a, int *b)
{
	int swap;

	swap = *a;
	*a = *b;
	*b = swap;
}

int partionning(int *arr, int start, int end)
{
	int pindex;
	int pivot;
	int i;

	pindex = start;
	pivot = arr[end];
	i = start ;
	while (i < end)
	{
		if (arr[i] <= pivot)
		{
			swap(&arr[i], &arr[pindex]);
			pindex++;
		}
		i++;
	}
	swap(&arr[end], &arr[pindex]);
	return (pindex);
}

int *quicksort(int *arr, int start, int end)
{
	int pindex;

	if (start >= end)
		return (0);
	pindex = partionning(arr, start, end);
	quicksort(arr, start, pindex - 1);
	quicksort(arr, pindex + 1, end);
	return (arr);
}
