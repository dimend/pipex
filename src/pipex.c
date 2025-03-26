/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:14:41 by dimendon          #+#    #+#             */
/*   Updated: 2025/03/26 20:10:38 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

void	execute(char *argv, char **envp, int checkcmd, int *pipefd)
{
	char	**cmd;
	char	*path;
	int		i;

	i = -1;
	cmd = NULL;
    path = NULL;
    
	if (checkcmd == 0)
	{
		cmd = ft_split(argv, ' ');
		path = get_path(envp, cmd, pipefd);
	}
	else
	{
		path = choosecmd(argv);
		cmd = ft_split(path, ' ');
		free(path);
		path = ft_strdup("");
		path = ft_strcatrealloc(path, argv);
		path = ft_strtok(path, ' ');
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

// read from infile, write to pipe
void	readchild(char **argv, char **envp, int *pipefd)
{
	int		file;
	char	*filename;
	char	*cmds;
	int		checkcmds;

	cmds = ft_strdup(argv[2]);
	checkcmds = checkcmd(cmds, pipefd);
	filename = ft_strdup(argv[1]);
	close(pipefd[0]);
	file = open(filename, O_RDONLY);
	if (file == -1)
		error(filename, "No such file or directory", 1, pipefd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	dup2(file, STDIN_FILENO);
	close(file);
	free(filename);
	if (checkcmds < 0)
	{
		error(NULL, "command not found", 127, pipefd);
	}
	execute(argv[2], envp, checkcmds, pipefd);
}

// read from pipe write to outfile
void	writechild(char **argv, char **envp, int *pipefd)
{
	int		file;
	char	*filename;
	char	*cmds;
	int		checkcmds;

	cmds = ft_strdup(argv[3]);
	checkcmds = checkcmd(cmds, pipefd);
	filename = ft_strdup(argv[4]);
	file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
		error(filename, "perror", 1, pipefd);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	dup2(file, STDOUT_FILENO);
	close(file);
	free(filename);
	if (checkcmds < 0)
	{
		error(NULL, "command not found", 127, pipefd);
	}
	execute(argv[3], envp, checkcmds, pipefd);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		signal_number;
	int		status1;
	int		status2;

	status1 = 0;
	status2 = 0;
	if (argc == 5)
	{
		if (pipe(pipefd) == -1)
			error(argv[1], "pipefd1", 1, pipefd);
		pid1 = fork();
		if (pid1 == -1)
			error(argv[1], "fork1", 1, pipefd);
		if (pid1 == 0)
			readchild(argv, envp, pipefd);
		pid2 = fork();
		if (pid2 == -1)
			error(argv[4], "fork2", 1, pipefd);
		if (pid2 == 0)
			writechild(argv, envp, pipefd);
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(pid1, &status1, 0);
		waitpid(pid2, &status2, 0);
		if (status1 == 0 || status2 == 0)
			return (0);
	}
	else
		error(NULL, "Usage: ./pipex infile cmd1 cmd2 outfile", 1, pipefd);
	if (WIFSIGNALED(status2))
	{
		signal_number = WTERMSIG(status2);
		return (128 + signal_number);
	}
	return (WEXITSTATUS(status2));
}
