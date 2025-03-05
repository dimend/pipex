/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:54:55 by dimendon          #+#    #+#             */
/*   Updated: 2024/11/11 16:55:15 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int input)
{
	if (((input < 65 || input > 90) && (input < 97 || input > 122)
			&& (input < 48 || input > 57)))
		return (0);
	return (1);
}
