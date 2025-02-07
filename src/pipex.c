#include "pipex.h"

void error_exit(char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void pid_handler(pid_t pid, int pipefd[2], short int read_end, char *cmd)
{
    if (pid == 0)
    {
        char *cmds[] = {cmd, "hello", NULL};

        if (read_end == 1)
        {
            close(pipefd[0]);
            dup2(pipefd[1], 1);
            close(pipefd[1]);
        }
        else if (read_end == 0)
        {
            close(pipefd[1]);
            dup2(pipefd[0], 0);
            close(pipefd[0]);
        }

        if (execvp(cmds[0], cmds) == -1)
            error_exit("Execvp failed for ");
    }
}

int main() 
{
    int pipefd[2];
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1)
        error_exit("Error creating pipe");

    pid1 = fork();
    if (pid1 == -1)
        error_exit("Error forking first process");

    if (pid1 == 0)
        pid_handler(pid1, pipefd, 1, "echo");

    pid2 = fork();
    if (pid2 == -1)
        error_exit("Error forking second process");
    if (pid2 == 0)
        pid_handler(pid2, pipefd, 0, "grep");

    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}
