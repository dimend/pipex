/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:19:03 by dimendon          #+#    #+#             */
/*   Updated: 2024/11/11 16:55:58 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	size;
	size_t			remain;
	size_t			i;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (start >= size)
		return (ft_strdup(""));
	else
	{
		remain = size - start;
		if (remain > len)
			remain = len;
		substr = malloc(remain + 1);
		if (substr == NULL)
			return (NULL);
		i = 0;
		while (i < remain)
			substr[i++] = s[start++];
		substr[i] = '\0';
	}
	return (substr);
}
