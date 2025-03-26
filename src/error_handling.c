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

static int	is_folder(char *cmd)
{
	int	fd_test;

	fd_test = open(cmd, O_DIRECTORY);
	if (fd_test != -1)
	{
		close(fd_test);
		return (126);
	}
	return (0);
}

int	checkcmd(char *cmd, int *pipefd)
{
	int	directory;
	int	i;

	directory = 0;
	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '/')
			directory++;
		i++;
	}
	if (cmd[0] == '\0')
		return (-1);
	if (is_folder(cmd) == 126)
		error(cmd, "Is a directory", 126, pipefd);
	free(cmd);
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
	if (cmd)
		free(cmd);
	exit(exitcode);
}
