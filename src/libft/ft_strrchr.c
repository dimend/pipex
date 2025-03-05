/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:47:44 by dimendon          #+#    #+#             */
/*   Updated: 2024/11/11 16:55:54 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *input, int findascii)
{
	int	size;

	size = 0;
	while (input[size])
		size++;
	findascii %= 256;
	while (size >= 0)
	{
		if (input[size] == findascii)
			return ((char *)(input + size));
		size--;
	}
	return (NULL);
}
