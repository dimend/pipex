/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:47:59 by dimendon          #+#    #+#             */
/*   Updated: 2024/11/11 16:55:43 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	totalsize;

	totalsize = ft_strlen(s1) + ft_strlen(s2) + 1;
	ret = malloc(totalsize);
	if (!ret)
		return (NULL);
	ft_bzero(ret, totalsize);
	ft_strlcpy(ret, s1, totalsize);
	ft_strlcat(ret, s2, totalsize);
	return (ret);
}
