#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

char    *get_path(char **envp, char **cmd, int *pipefd);
int     checkcmd(char *cmd, int *pipefd);
void    error(char *cmd, char *message, int exitcode, int *pipefd);
char    *choosecmd(char *argv);

#endif
