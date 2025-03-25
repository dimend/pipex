#include "libft.h"

char *ft_strcatrealloc(char *src, const char *new)
{
    char *newdata;
    int src_len;
    int new_len;

    src_len = ft_strlen(src);
    new_len = ft_strlen(new);

    newdata = malloc(src_len + new_len + 1);
    if (!newdata)
        return NULL;

    ft_memcpy(newdata, src, src_len);
    ft_memcpy(newdata + src_len, new, new_len + 1);

    free(src);
    return (newdata);
}
