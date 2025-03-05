/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:54:45 by dimendon          #+#    #+#             */
/*   Updated: 2024/11/12 14:50:47 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	getsize(int n)
{
	unsigned int	size;

	size = 0;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static void	passtostring(unsigned int size, unsigned int n, char *s,
		short int isnegative)
{
	if (isnegative == 1)
	{
		n = n * -1;
		s[0] = '-';
		while (size > 1)
		{
			s[size - 1] = (n % 10) + '0';
			n = n / 10;
			size--;
		}
	}
	else
	{
		while (size > 0)
		{
			s[size - 1] = (n % 10) + '0';
			n = n / 10;
			size--;
		}
	}
}

char	*ft_itoa(int n)
{
	char			*ret;
	unsigned int	size;

	if (n == 0)
		return (ft_strdup("0"));
	else if (n < 0)
	{
		size = getsize(n * -1) + 1;
		ret = ft_calloc(size + 1, 1);
		if (!ret)
			return (NULL);
		passtostring(size, n, ret, 1);
	}
	else if (n > 0)
	{
		size = getsize(n);
		ret = ft_calloc(size + 1, 1);
		if (!ret)
			return (NULL);
		passtostring(size, n, ret, 0);
	}
	else
		return (NULL);
	return (ret);
}
