/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:47:39 by dimendon          #+#    #+#             */
/*   Updated: 2024/11/13 17:19:11 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static short int	checkset(const char s1, const char *set, size_t setsize)
{
	size_t	i;

	i = 0;
	while (i < setsize)
	{
		if (s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	size_t	totalsize;
	size_t	fw;
	size_t	i;

	totalsize = ft_strlen(s1);
	fw = 0;
	while (checkset(s1[fw], set, ft_strlen(set)) == 1)
		fw++;
	while (checkset(s1[totalsize - 1], set, ft_strlen(set)) == 1)
		totalsize--;
	if (fw >= totalsize)
		return (ft_strdup("\0"));
	ret = malloc((totalsize - fw) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < (totalsize - fw))
	{
		ret[i] = s1[i + fw];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
