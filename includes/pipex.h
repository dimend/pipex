#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>

char **get_all_paths(char **envp);
char *get_path(char **envp, char *cmd);
short int checkargs(char *file, char *cmd);
void error(char *cmd, char *message, int exitcode);

#endif
