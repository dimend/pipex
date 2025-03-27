/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:21:45 by dimendon          #+#    #+#             */
/*   Updated: 2025/03/26 20:10:59 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

static int	is_folder(char *arg)
{
	int	fd_test;

	fd_test = open(arg, O_DIRECTORY);
	if (fd_test != -1)
	{
		close(fd_test);
		return (126);
	}
	return (0);
}

int	checkargs(char *arg, int *pipefd)
{
	int	directory;
	int	i;

	directory = 0;
	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '/')
			directory++;
		i++;
	}
	if (is_folder(arg) == 126)
		error(arg, "Is a directory", 126, pipefd);
	return (directory);
}

char	*choosecmd(char *argv)
{
	char	**cmd;
	char	*result;
	int		i;

	cmd = NULL;
	i = 0;
	cmd = ft_split(argv, '/');
	while (cmd[i])
		i++;
	result = ft_strdup(cmd[i - 1]);
	i = -1;
	while (cmd[++i])
		free(cmd[i]);
	free(cmd);
	return (result);
}

void	error(char *cmd, char *message, int exitcode, int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	if (message[0] == 'p')
	{
		ft_putstr_fd("./pipex: : ", 2);
		if (cmd)
			perror(cmd);
		else
			ft_putstr_fd(message, 2);
	}
	else
	{
		ft_putstr_fd("./pipex: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(message, 2);
		write(2, "\n", 1);
	}
	if (cmd && exitcode == 127)
		free(cmd);
	exit(exitcode);
}
