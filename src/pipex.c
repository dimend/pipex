/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 17:14:41 by dimendon          #+#    #+#             */
/*   Updated: 2025/04/02 17:24:04 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

void	readchild(char **argv, char **envp, int *pipefd)
{
	int	file;

	close(pipefd[0]);
	file = open(argv[1], O_RDONLY);
	if (file == -1)
		error(argv[1], strerror(errno), 1, pipefd);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		error(NULL, "dup2 pipefd[1] failed", 1, pipefd);
	close(pipefd[1]);
	if (dup2(file, STDIN_FILENO) == -1)
		error(NULL, "dup2 file failed", 1, pipefd);
	close(file);
	if (argv[2][0] == '\0')
		error(NULL, "command not found", 127, pipefd);
	execute(argv[2], envp, pipefd);
}

void	writechild(char **argv, char **envp, int *pipefd)
{
	int	file;

	file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
		error(argv[4], strerror(errno), 1, pipefd);
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		error(NULL, "dup2 pipefd[0] failed", 1, pipefd);
	close(pipefd[0]);
	if (dup2(file, STDOUT_FILENO) == -1)
		error(NULL, "dup2 file failed", 1, pipefd);
	close(file);
	if (argv[3][0] == '\0')
		error(NULL, "command not found", 127, pipefd);
	execute(argv[3], envp, pipefd);
}

int	handle_child_process_status(pid_t pid1, pid_t pid2)
{
	int	status1;
	int	status2;
	int	signal_number;

	status1 = 0;
	status2 = 0;
	if (waitpid(pid1, &status1, 0) == -1)
		error(NULL, "waitpid1 failed", 1, NULL);
	if (waitpid(pid2, &status2, 0) == -1)
		error(NULL, "waitpid2 failed", 1, NULL);
	if (status1 == 0 || status2 == 0)
		return (0);
	if (WIFSIGNALED(status2))
	{
		signal_number = WTERMSIG(status2);
		return (128 + signal_number);
	}
	return (WEXITSTATUS(status2));
}

void	create_child_processes(char **argv, char **envp, pid_t *pid1,
		pid_t *pid2)
{
	int	pipefd[2];

	pipefd[0] = -1;
	pipefd[1] = -1;
	if (pipe(pipefd) == -1)
		error(argv[1], "fail pipefd1", 1, pipefd);
	*pid1 = fork();
	if (*pid1 == -1)
		error(argv[1], "fail fork1", 1, pipefd);
	if (*pid1 == 0)
		readchild(argv, envp, pipefd);
	*pid2 = fork();
	if (*pid2 == -1)
		error(argv[4], "fail fork2", 1, pipefd);
	if (*pid2 == 0)
		writechild(argv, envp, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;

	if (argc == 5)
	{
		create_child_processes(argv, envp, &pid1, &pid2);
		return (handle_child_process_status(pid1, pid2));
	}
	else
		error(NULL, "Usage: ./pipex infile cmd1 cmd2 outfile", 1, NULL);
	return (0);
}
