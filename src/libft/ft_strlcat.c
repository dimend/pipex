/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:47:57 by dimendon          #+#    #+#             */
/*   Updated: 2024/11/11 16:55:45 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dest_len;
	size_t	i;

	src_len = 0;
	while (src[src_len])
		src_len++;
	dest_len = 0;
	while (dest_len < dstsize && dst[dest_len])
		dest_len++;
	if (dest_len == dstsize)
		return (dest_len + src_len);
	i = 0;
	while (src[i] && (dest_len + i + 1) < dstsize)
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	if ((dest_len + i) < dstsize)
		dst[dest_len + i] = '\0';
	return (dest_len + src_len);
}
