/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:03:48 by dimendon          #+#    #+#             */
/*   Updated: 2024/11/12 18:36:34 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_printbackwards(char *converted, int fd)
{
	int	i;

	i = 0;
	while (*converted != '\0')
	{
		i++;
		converted++;
	}
	while (i > 0)
	{
		converted--;
		write(fd, &*converted, 1);
		i--;
	}
}

static void	assignvalues(char *s, int n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		s[i] = (n % 10) + 48;
		n = n / 10;
		i++;
	}
	s[i] = '\0';
}

void	ft_putnbr_fd(int n, int fd)
{
	char	nbtoch[11];

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	else if (n < 0)
	{
		n = n * (-1);
		write(fd, "-", 1);
	}
	else if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	assignvalues(nbtoch, n);
	ft_printbackwards(nbtoch, fd);
}
