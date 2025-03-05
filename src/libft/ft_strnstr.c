/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:47:49 by dimendon          #+#    #+#             */
/*   Updated: 2024/11/12 14:18:49 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	char	*ret;
	size_t	i;
	size_t	size_tf;

	if (!str && len == 0)
		return (NULL);
	if (*to_find == '\0')
		return ((char *)str);
	size_tf = 0;
	while (to_find[size_tf] != '\0')
		size_tf++;
	while (*str != '\0' && len >= size_tf)
	{
		ret = (char *)str;
		i = 0;
		while (str[i] == to_find[i])
		{
			i++;
			if (i == size_tf)
				return (ret);
		}
		str++;
		len--;
	}
	return (NULL);
}
