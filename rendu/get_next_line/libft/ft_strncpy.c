/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 13:16:25 by bduron            #+#    #+#             */
/*   Updated: 2016/11/29 10:17:46 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char *p;

	p = dst;
	while (len && *src)
	{
		*p++ = *src++;
		len--;
	}
	while (len)
	{
		*p++ = '\0';
		len--;
	}
	return (dst);
}
