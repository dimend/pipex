/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:14:26 by dimendon          #+#    #+#             */
/*   Updated: 2025/03/26 19:19:12 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

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
	finalpath = NULL;
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		paths[i] = ft_strcatrealloc(paths[i], "/");
		paths[i] = ft_strcatrealloc(paths[i], cmd[0]);
		if (access(paths[i], F_OK) == 0)
		{
			finalpath = ft_strdup(paths[i]);
			break ;
		}
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	if(!finalpath)
	{
		i = -1;
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error(NULL,"command not found",127, pipefd);	
	}
	return (finalpath);
}

