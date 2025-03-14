#include "pipex.h"
#include "libft/libft.h"

char **get_all_paths(char **envp)
{
    int i;
    char **paths = NULL;

    i = 0;
    while(envp[i])
    {
        if(ft_strncmp("PATH", envp[i], 4) == 0)
        {
            paths = ft_split(envp[i] + 5, ':');
            if (paths == NULL)
                return NULL;
            break;
        } 
        i++;
    }
    return (paths);
}

char *get_path(char **envp, char *cmd)
{
    int i;
    char **paths;
    char *finalpath;

    paths = get_all_paths(envp);
    if (!paths)
        return (NULL);
    i = 0;
    while(paths[i])
    {
        paths[i] = ft_strcatrealloc(paths[i], "/");
        paths[i] = ft_strcatrealloc(paths[i], cmd);
        if (access(paths[i], F_OK) == 0)
        {
            finalpath = ft_strdup(paths[i]);
            i = -1;
            while (paths[++i])
			    free(paths[i]);
            free(paths);
            return (finalpath);
        }
        i++;
    }
    i = -1;
    while (paths[++i])
		free(paths[i]);
    free(paths);
    return (NULL);
}

short int checkargs(char *file, char *cmd)
{
    char *result = ft_strdup("");

    if(!file || file[0] == '\0')
        error(result, "No such file or directory", 1);

    if(!cmd || cmd[0] == '\0')
        error(result, "comand not found", 127);

    free(result);
    return (0);
}