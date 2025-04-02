/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimendon <dimendon@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:14:28 by dimendon          #+#    #+#             */
/*   Updated: 2025/04/02 16:14:29 by dimendon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

char	*get_path(char **envp, char **cmd, int *pipefd);
int		checkargs(char *cmd, int *pipefd);
void	error(char *cmd, char *message, int exitcode, int *pipefd);
char	*choosecmd(char *argv);
void	execute(char *argv, char **envp, int *pipefd);
char	*parse_command_and_path(char *argv, char **envp, char ***cmd,
			int *pipefd);

#endif
