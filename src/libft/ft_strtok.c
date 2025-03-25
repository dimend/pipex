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