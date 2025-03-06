#include "pipex.h"
#include "libft/libft.h"
#include <stdio.h>

void error(char *cmd, char *message, int exitcode)
{
    if(message[0] == 'p')
    {
        ft_putstr_fd("./pipex: ", 2);
        perror(cmd);
    }
    else
    {
        ft_putstr_fd("./pipex: ", 2);
        ft_putstr_fd(cmd, 2);
        ft_putstr_fd(": ", 2);
        ft_putstr_fd(message, 2);
        write(2,"\n", 1);
    }
    free(cmd);
    exit(exitcode);
}

char **get_all_paths(char **envp)
{
    int i;
    char **paths = NULL;

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
    if (!paths)
        return (NULL);
    i = 0;
    while(paths[i])
    {
        paths[i] = ft_strcatrealloc(paths[i], "/");
        paths[i] = ft_strcatrealloc(paths[i], cmd);
        if (access(paths[i], F_OK) == 0)
        {
            finalpath = ft_strdup(paths[i]);
            i = -1;
            while (paths[++i])
			    free(paths[i]);
            return (finalpath);
        }
        i++;
    }
    i = -1;
    while (paths[++i])
		free(paths[i]);
    free(paths);
    return (NULL);
}

void execute(char *argV, char **envp)
{
	char	**cmd;
	int 	i;
	char	*path;
    char    *command;

	i = -1;
	cmd = ft_split(argV, ' ');
	path = get_path(envp, cmd[0]);
    command = ft_strdup(cmd[0]);

    if(ft_strncmp(command,"test",4))
    {
        printf("test");
    }

	if (!path)	
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
        error(command, "command not found", 127);
	}

	if (execve(path, cmd, envp) == -1)
		error(argV ,"execve", 1);
    free(path);
    free(command);
}

void pid_handler(char **argV, char **envp, int *pipefd, short int read)
{
	int		file;
    char    *filename;

    if(read == 0)
    {
        filename = ft_strdup(argV[1]);
        close(pipefd[0]);
        file = open(filename, O_RDONLY, 0777);
        if (file == -1)
		    error(filename, "perror", 1);
        dup2(pipefd[1], STDOUT_FILENO); //dup pipefd and assign stdout so that stdout goes to the pipe
        close(pipefd[1]);
	    dup2(file, STDIN_FILENO);       //dup file and assign stdin to read from file and not stdin
        close(file);
        free(filename);
	    execute(argV[2], envp);
    }
    else
    {
        filename = ft_strdup(argV[4]);
	    file = open(argV[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	    if (file == -1)
		    error(filename, "perror", 1);
        close(pipefd[1]);
	    dup2(pipefd[0], STDIN_FILENO);  //dup pipefd to stin to read from pipe
        close(pipefd[0]);
	    dup2(file, STDOUT_FILENO);      //dup file to stdout so it writes to file
        close(file);
        free(filename);
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
            error(argV[1], "pipefd1", 1);

        pid = fork();
        if(pid == -1)
            error(argV[1], "pipefd2", 1);
        
        if(pid == 0)
            pid_handler(argV, envp, pipefd, 0); //child
        
        waitpid(pid, NULL, 0);
        pid_handler(argV, envp, pipefd, 1);     //parent
    }
    return 0;
}
