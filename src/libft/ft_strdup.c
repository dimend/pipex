/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:54:29 by dimendon          #+#    #+#             */
/*   Updated: 2024/11/11 19:34:29 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dupe;
	int		size;

	size = 0;
	while (src[size])
	{
		size++;
	}
	dupe = malloc(size + 1);
	if (!dupe)
		return (NULL);
	size = 0;
	while (*src)
	{
		dupe[size] = *src;
		src++;
		size++;
	}
	dupe[size] = '\0';
	return (dupe);
}
