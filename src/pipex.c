#include "pipex.h"
#include "libft/libft.h"
#include <stdio.h>

void error(char *cmd, char *message, int exitcode)
{
    if(message[0] == 'p')
    {
        ft_putstr_fd("./pipex: : ", 2);
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
    if (cmd)
        free(cmd);
    exit(exitcode);
}

void execute(char *argv, char **envp, int directory)
{
	char	**cmd;
	int 	i;
	char	*path;
    char    *command;

	i = -1;
	cmd = ft_split(argv, ' ');
	path = get_path(envp, cmd[0]);
    command = ft_strdup(cmd[0]); 
	if(!path || cmd[0][0] == '\0')	
	{
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
	}
	if (execve(path, cmd, envp) == -1)
    {
        free(path);
        while (cmd[++i])
            free(cmd[i]);
        free(cmd);
		error(command ,"execve failed", 1);        
    }
    free(path);
    free(command);
}

//read from infile, write to pipe
void readchild(char **argV, char **envp, int *pipefd)
{
    int		file;
    char    *filename;
    int directory;

    directory = checkcmd(argV[2]);
    filename = ft_strdup(argV[1]);
    close(pipefd[0]);
    file = open(filename, O_RDONLY);
    if (file == -1)
		error(filename, "perror", 1);
    dup2(pipefd[1], STDOUT_FILENO); //dup pipefd and assign stdout so that stdout goes to the pipe
    close(pipefd[1]);
    dup2(file, STDIN_FILENO);       //dup file and assign stdin to read from file and not stdin
    close(file);
    free(filename);
	execute(argV[2], envp, directory);
}

//read from pipe write to outfile
void writechild(char **argV, char **envp, int *pipefd)
{
    int		file;
    char    *filename;

    //checkargs(argV[4], argV[3]);
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
	execute(argV[3], envp, directory);
}


int main(int argC, char **argV, char **envp) 
{
    int pipefd[2];
    pid_t pid1, pid2;
    int status1, status2;

    status1 = 0;
    status2 = 0;
    if(argC == 5)
    {
        if(pipe(pipefd) == -1)
            error(argV[1], "pipefd1", 1);

        pid1 = fork();
        if(pid1 == -1)
            error(argV[1], "fork1", 1);

        if(pid1 == 0)
            readchild(argV, envp, pipefd);

        pid2 = fork();
        if(pid2 == -1)
            error(argV[4], "fork2", 1);
        
        if(pid2 == 0)
            writechild(argV, envp, pipefd);

        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(pid1, &status1, 0);
        waitpid(pid2, &status2, 0);
        if(status1 == 0 || status2 == 0)
            return (0);
    }
    else
        error(NULL, "Usage: ./pipex infile cmd1 cmd2 outfile", 1);
    return (WEXITSTATUS(status2));
}

