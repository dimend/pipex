#include "libft.h"

char	*ft_strcatrealloc(char *src, const char *new)
{
	char	*newdata;
    int		src_len;
	int		new_len;
	int		i;

	src_len = ft_strlen(src);
	new_len = ft_strlen(new);
    i = 0;
	newdata = malloc(src_len + new_len + 1);
	if (!newdata)
		return (NULL);
	while (i < src_len)
	{
		newdata[i] = src[i];
		i++;
	}
	i = 0;
	while (i < new_len)
	{
		newdata[src_len + i] = new[i];
		i++;
	}
	newdata[src_len + new_len] = '\0';
	free(src);
	return (newdata);
}
