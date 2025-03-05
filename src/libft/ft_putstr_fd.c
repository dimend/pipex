/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:15:12 by dimendon          #+#    #+#             */
/*   Updated: 2024/11/12 17:02:42 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	char	*ptr;
	int		strlen;

	if (!s)
		return ;
	if (fd < 0)
		return ;
	ptr = s;
	strlen = 0;
	while (*ptr != '\0')
	{
		ptr++;
		strlen++;
	}
	write(fd, s, strlen);
}
