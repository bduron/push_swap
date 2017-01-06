/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 09:04:06 by bduron            #+#    #+#             */
/*   Updated: 2016/11/29 10:16:30 by bduron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *last_pos;

	last_pos = NULL;
	while (*s)
	{
		if (*s == c)
			last_pos = (char *)s;
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (last_pos);
}
