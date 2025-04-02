/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcatrealloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:15:10 by dimendon          #+#    #+#             */
/*   Updated: 2025/03/26 17:15:30 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcatrealloc(char *src, const char *new)
{
	char	*newdata;
	int		src_len;
	int		new_len;

	if (!src)
		src_len = 0;
	else
		src_len = ft_strlen(src);
	new_len = ft_strlen(new);
	newdata = malloc(src_len + new_len + 1);
	if (!newdata)
		return (NULL);
	if (src)
		ft_memcpy(newdata, src, src_len);
	ft_memcpy(newdata + src_len, new, new_len + 1);
	free(src);
	return (newdata);
}
