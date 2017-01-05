/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 10:16:12 by bduron            #+#    #+#             */
/*   Updated: 2016/11/29 10:27:39 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memalloc(size_t size)
{
	char *s;

	if (!size)
		return (NULL);
	s = malloc(size);
	if (!s)
		return (NULL);
	if (!ft_memset(s, 0, size))
		return (NULL);
	return (s);
}
