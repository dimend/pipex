/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 16:54:33 by dimendon          #+#    #+#             */
/*   Updated: 2024/11/13 17:18:45 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	skipc(const char *input, const char c, size_t pos)
{
	while (input[pos] == c)
		pos++;
	return (pos);
}

static size_t	ft_substrlen(const char *input, const char c, unsigned int pos,
		unsigned int lastchar)
{
	size_t	len;

	len = 0;
	while (input[pos] == c && pos < lastchar)
		pos++;
	while (input[pos] != c && pos < lastchar)
	{
		len++;
		pos++;
	}
	return (len);
}

static unsigned int	countwords(const char *s, const char c,
		unsigned int lastchar)
{
	unsigned int	i;
	unsigned int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] == c && i < lastchar)
			i++;
		if (s[i] != c && i < lastchar)
		{
			words++;
			while (s[i] != c && i < lastchar)
				i++;
		}
	}
	return (words);
}

static char	**free_words(char **words, unsigned int i)
{
	while (i > 0)
		free(words[--i]);
	free(words);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char			**words;
	unsigned int	nrwords;
	unsigned int	pos;
	unsigned int	sublen;
	unsigned int	i;

	nrwords = countwords(s, c, ft_strlen(s));
	words = malloc((nrwords + 1) * sizeof(char *));
	if (!words)
		return (NULL);
	pos = 0;
	i = 0;
	while (i < nrwords)
	{
		sublen = ft_substrlen(s, c, pos, ft_strlen(s));
		words[i] = malloc(sublen + 1);
		if (!words[i])
			return (free_words(words, i));
		pos = skipc(s, c, pos) + sublen;
		ft_strlcpy(words[i], s + (pos - sublen), sublen + 1);
		i++;
	}
	words[i] = NULL;
	return (words);
}
