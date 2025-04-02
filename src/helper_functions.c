/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:04:24 by dimendon          #+#    #+#             */
/*   Updated: 2025/04/02 16:12:55 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

char	*handle_directory_case(char *argv, char ***cmd, char **path,
		int *pipefd)
{
	*path = choosecmd(argv);
	if (*path == NULL)
		error(NULL, "Malloc fail", -1, pipefd);
	*cmd = ft_split(*path, ' ');
	free(*path);
	if (!*cmd)
		error(NULL, "Malloc fail", -1, pipefd);
	*path = NULL;
	*path = ft_strcatrealloc(*path, argv);
	if (!*path)
		error(NULL, "Malloc fail", -1, pipefd);
	*path = ft_strtok(*path, ' ');
	return (*path);
}

char	*parse_command_and_path(char *argv, char **envp, char ***cmd,
		int *pipefd)
{
	char	*path;
	int		isdirectory;

	*cmd = NULL;
	path = NULL;
	isdirectory = checkargs(argv, pipefd);
	if (isdirectory == 0)
	{
		*cmd = ft_split(argv, ' ');
		if (*cmd == NULL)
			error(NULL, "Malloc fail", -1, pipefd);
		path = get_path(envp, *cmd, pipefd);
	}
	else
		path = handle_directory_case(argv, cmd, &path, pipefd);
	return (path);
}
