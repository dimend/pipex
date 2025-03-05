/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:54:31 by dimendon          #+#    #+#             */
/*   Updated: 2024/11/11 16:55:39 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *input, int findascii)
{
	findascii %= 256;
	while (*input)
	{
		if (*input == findascii)
			return ((char *)input);
		input++;
	}
	if (findascii == 0)
	{
		return ((char *)input);
	}
	return (NULL);
}
