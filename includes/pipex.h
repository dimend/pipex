#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

char *get_path(char **envp, char *cmd);
int checkcmd(char *cmd);
void error(char *cmd, char *message, int exitcode);

#endif
