/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:54:41 by dimendon          #+#    #+#             */
/*   Updated: 2024/11/11 16:55:29 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t num)
{
	const unsigned char	*p = (const unsigned char *)ptr;
	size_t				i;

	i = 0;
	while (i < num)
	{
		if (p[i] == (unsigned char)value)
			return ((void *)(p + i));
		else
			i++;
	}
	return (0);
}
