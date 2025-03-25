#include "pipex.h"
#include "libft/libft.h"

char **get_all_paths(char **envp)
{
    int i;
    char **paths = NULL;

    i = 0;
    while(envp[i])
    {
        if(envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && envp[i][3] == 'H')
        {
            paths = ft_split(envp[i] + 5, ':');
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
    finalpath = NULL;
    if (!paths)
        return (NULL);
    i = -1;
    while(paths[++i])
    {
        paths[i] = ft_strcatrealloc(paths[i], "/");
        paths[i] = ft_strcatrealloc(paths[i], cmd);
        if (access(paths[i], F_OK) == 0)
        {
            finalpath = ft_strdup(paths[i]);
            break;
        }
    }
    i = -1;
    while (paths[++i])
		free(paths[i]);
    free(paths);
    return (finalpath);
}

int checkcmd(char *cmd)
{
    int directory;
    int i;

    directory = 0;
    i = 0;    
    while(cmd[i] != '\0')
    {
        if(cmd[i] == '/')
            directory++;
        i++;
    }

    if(cmd[0] == '\0')
        return (-1);

    return (directory);
}
