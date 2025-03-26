/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:15:20 by dimendon          #+#    #+#             */
/*   Updated: 2025/03/26 17:15:24 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char delim)
{
	static char	*input;
	char		*start;

	if (str)
		input = str;
	if (!input)
		return (NULL);
	while (*input != '\0' && *input == delim)
		input++;
	if (*input == '\0')
		return (NULL);
	start = input;
	while (*input != '\0' && *input != delim)
		input++;
	if (*input == delim)
	{
		*input = '\0';
		input++;
	}
	if (*input == '\0')
		input = NULL;
	return (start);
}
