/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:14:26 by dimendon          #+#    #+#             */
/*   Updated: 2025/03/27 20:22:53 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

void	freepath_checkfinalpath(char **paths, char *finalpath, char **cmd, int *pipefd)
{
	int i;

	i = -1;
	if(!finalpath && !paths)
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error(NULL, "Malloc fail", -1, pipefd);
	}
	while (paths[++i])
		free(paths[i]);
	free(paths);
	if(!finalpath)
	{
		finalpath = ft_strdup(cmd[0]);
		i = -1;
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error(finalpath,"command not found",127,pipefd);	
	}
}

char	**get_all_paths(char **envp)
{
	int		i;
	char	**paths;

	paths = NULL;
	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T'
			&& envp[i][3] == 'H')
		{
			/// check for malloc fail
			paths = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (paths);
}

char	*get_path(char **envp, char **cmd, int *pipefd)
{
	int		i;
	char	**paths;
	char	*finalpath;

	paths = get_all_paths(envp);
	if (!paths)
		return (NULL);
	finalpath = NULL;
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strcatrealloc(paths[i], "/");
		if(paths[i])
			paths[i] = ft_strcatrealloc(paths[i], cmd[0]);
		if (paths[i] && access(paths[i], F_OK) == 0)
		{
			finalpath = ft_strdup(paths[i]);
			break ;
		}
	}
	freepath_checkfinalpath(paths, finalpath, cmd, pipefd);
	return (finalpath);
}

char *parse_command_and_path(char *argv, char **envp, char ***cmd, int *pipefd)
{
    char *path;
	int isdirectory;

	*cmd = NULL;
    path = NULL;
	isdirectory = checkargs(argv, pipefd);
    if (isdirectory == 0)
    {
        *cmd = ft_split(argv, ' ');
		if(*cmd == NULL)
			error(NULL, "Malloc fail", -1, pipefd)
        path = get_path(envp, *cmd, pipefd);
    }
	else
    {
        path = choosecmd(argv);
		if (path == NULL)
			error(NULL, "Malloc fail", -1, pipefd)
        *cmd = ft_split(path, ' ');
        free(path);
		if(!cmd)
			error(NULL, "Malloc fail", -1, pipefd)
        path = ft_strcatrealloc(path, argv);
		if(!path)
			error(NULL, "Malloc fail", -1, pipefd)
        path = ft_strtok(path, ' ');
    }
    return (path);
}

void	execute(char *argv, char **envp, int *pipefd)
{
	char	**cmd;
	char	*path;
	char	*auxcmd;
	int		i;

	i = -1;
	cmd = NULL;
	auxcmd = NULL;
    path = parse_command_and_path(argv, envp, &cmd, pipefd);
	if(path == NULL)
	{
		auxcmd = ft_strdup(cmd[0]);
		while (cmd[++i])
            free(cmd[i]);
        free(cmd);
		if(!auxcmd)
			error(NULL, "Malloc fail", -1, pipefd)
		error(auxcmd, "No such file or directory", 127, pipefd);
	}
	if (execve(path, cmd, envp) == -1)
    {
        while (cmd[++i])
            free(cmd[i]);
        free(cmd);
        error(path, "No such file or directory", 127, pipefd);
    }
	free(path);
}

