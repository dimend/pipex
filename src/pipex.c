#include "pipex.h"
#include "libft/libft.h"
#include <stdio.h>

void error()
{
    perror("Error");
    exit(EXIT_FAILURE);
}

char **get_all_paths(char **envp)
{
    int i;
    char **paths;

    i = 0;
    while(envp[i])
    {
        if(envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && envp[i][3] == 'H')
        {
            paths = ft_split(envp[i] + 5, ':');
            break;
        } 
        i++;
    }
    return (paths);
}

char *get_path(char **envp, char *cmd)
{
    int i;
    char **paths;
    char *finalpath;

    paths = get_all_paths(envp);
    i = 0;
    while(paths[i])
    {
        paths[i] = ft_strjoin(paths[i], "/");
        paths[i] = ft_strjoin(paths[i], cmd);
        if (access(paths[i], F_OK) == 0)
        {
            finalpath = ft_strdup(paths[i]);
            i = 0;
            while (paths[++i])
			    free(paths[i]);
            return (finalpath);
        }
        i++;
    }
    return (NULL);
}

void execute(char *argV, char **envp)
{
	char	**cmd;
	int 	i;
	char	*path;
	
	i = -1;
	cmd = ft_split(argV, ' ');
	path = get_path(envp, cmd[0]);
	if (!path)	
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		error();
	}
	if (execve(path, cmd, envp) == -1)
		error();
}

void pid_handler(char **argV, char **envp, int *pipefd, short int read)
{
	int		file;

    if(read == 0)
    {
        file = open(argV[1], O_RDONLY, 777);
        dup2(pipefd[1], STDOUT_FILENO); //dup pipefd and assign stdout so that stdout goes to the pipe
	    dup2(file, STDIN_FILENO);       //dup file and assign stdin to read from file and not stdin
        if (file == -1)
		    error();
	    close(pipefd[0]);
	    execute(argV[2], envp);
    }
    else
    {
	    file = open(argV[4], O_WRONLY | O_CREAT | O_TRUNC, 777);
	    if (file == -1)
		    error();
	    dup2(pipefd[0], STDIN_FILENO);  //dup pipefd to stin to read from pipe
	    dup2(file, STDOUT_FILENO);      //dup file to stdout so it writes to file
	    close(pipefd[1]);
	    execute(argV[3], envp);
    }
}

int main(int argC, char **argV, char **envp) 
{
    int pipefd[2];
    pid_t pid;

    if(argC == 5)
    {
        if(pipe(pipefd) == -1)
            error();
        pid = fork();
        if(pid == -1)
            error();
        if(pid == 0)
            pid_handler(argV, envp, pipefd, 0); //child
        waitpid(pid, NULL, 0);
        pid_handler(argV, envp, pipefd, 1);     //parent
    }
    return 0;
}
