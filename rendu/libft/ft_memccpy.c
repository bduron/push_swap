/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 09:44:54 by bduron            #+#    #+#             */
/*   Updated: 2016/11/29 10:26:48 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*d;
	const char		*s;

	d = dst;
	s = src;
	while (n--)
	{
		if (c == *s)
		{
			*d++ = *s++;
			return ((void *)d);
		}
		*d++ = *s++;
	}
	return (NULL);
}
