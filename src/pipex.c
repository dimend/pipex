#include "pipex.h"
#include "libft/libft.h"
#include <stdio.h>

void error(char *cmd, char *message, int exitcode)
{
    if(message[0] == 'p')
    {
        ft_putstr_fd("./pipex: : ", 2);
        if(cmd)
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
        write(2,"\n", 1);
    }
    if (cmd)
        free(cmd);
    exit(exitcode);
}

char *choosecmd(char *argv)
{
    char **cmd;
    char *result;
    int i;

    cmd = NULL;
    i = 0;
    cmd = ft_split(argv, '/');
    while(cmd[i])
        i++;
    result = ft_strdup(cmd[i - 1]);
    i = - 1;
    while (cmd[++i])
	    free(cmd[i]);
	free(cmd);
    return (result);
}

void execute(char *argv, char **envp, int checkcmd)
{
	char	**cmd;
	char	*path;
    int 	i;

	i = -1;
    cmd = NULL;
    if(checkcmd == 0)
    {
        cmd = ft_split(argv, ' ');
        path = get_path(envp, cmd[0]); 
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
		error(path, "No such file or directory", 127);        
    }
    free(path);
}

//read from infile, write to pipe
void readchild(char **argv, char **envp, int *pipefd)
{
    int		file;
    char    *filename;
    int     checkcmds;

    checkcmds = checkcmd(argv[2]);
    filename = ft_strdup(argv[1]);
    close(pipefd[0]);
    file = open(filename, O_RDONLY);
    if (file == -1)
		error(filename, "No such file or directory", 1);
    dup2(pipefd[1], STDOUT_FILENO); //dup pipefd and assign stdout so that stdout goes to the pipe
    close(pipefd[1]);
    dup2(file, STDIN_FILENO);       //dup file and assign stdin to read from file and not stdin
    close(file);
    free(filename);
    if(checkcmds < 0)
    {
        error(NULL, "command not found", 127);
    }
	execute(argv[2], envp, checkcmds);
}

//read from pipe write to outfile
void writechild(char **argv, char **envp, int *pipefd)
{
    int		file;
    char    *filename;
    int     checkcmds;

    checkcmds = checkcmd(argv[3]);
    filename = ft_strdup(argv[4]);
	file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
	    error(filename, "perror", 1);
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);  //dup pipefd to stin to read from pipe
    close(pipefd[0]);
	dup2(file, STDOUT_FILENO);      //dup file to stdout so it writes to file
    close(file);
    free(filename);
    if(checkcmds < 0)
    {
        error(NULL, "command not found", 127);
    }
	execute(argv[3], envp, checkcmds);
}

int main(int argc, char **argv, char **envp) 
{
    int pipefd[2];
    pid_t pid1, pid2;
    int status1, status2;

    status1 = 0;
    status2 = 0;
    if(argc == 5)
    {
        if(pipe(pipefd) == -1)
            error(argv[1], "pipefd1", 1);

        pid1 = fork();
        if(pid1 == -1)
            error(argv[1], "fork1", 1);

        if(pid1 == 0)
            readchild(argv, envp, pipefd);

        pid2 = fork();
        if(pid2 == -1)
            error(argv[4], "fork2", 1);
        
        if(pid2 == 0)
            writechild(argv, envp, pipefd);

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

