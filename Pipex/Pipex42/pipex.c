#include "pipex.h"

char *findPath(char **env, char **cmd)
{
    int i;
    int j;
    char **Paths;
    char *fullpath;
    char *tempPath;

    i = 0;
    while (env[i] != NULL)
    {
        if (ft_strncmp(env[i], "PATH=", 5) == 0)
        {
            Paths = ft_split(env[i] + 5, ':');
            j = 0;
            while (Paths[j] != NULL)
            {
                tempPath = ft_strjoin(Paths[j], "/");
                fullpath = ft_strjoin(tempPath, cmd[0]);
                free(tempPath);
                if (access(fullpath, X_OK) == 0)
                {
                    return fullpath;
                }
                free(fullpath);
                j++;
            }
        }
        i++;
    }
    return NULL;
}

void childProcess(int *fd, char **argv, char **env)
{
    int openFd;
    char **cmd;
    char *correctPath;
    
    close(fd[0]);
    cmd = ft_split(argv[2], ' ');
    openFd = open(argv[1], O_RDONLY);
    correctPath = findPath(env, cmd);
    printf("%s\n", correctPath);
    if (openFd == -1)
        return ;
    dup2(fd[1], STDOUT_FILENO);
    dup2(openFd, STDIN_FILENO);
    close(fd[1]);
    if (execve(correctPath, cmd, env) == -1)
    {
        printf("error execve");
    }
}

void parentProcess(int *fd, char **argv, char **env)
{
    int readFd;
    char **cmd;
    char *correctPath;

    close(fd[1]);
    cmd = ft_split(argv[3], ' ');
    readFd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    correctPath = findPath(env, cmd);
    printf("%s\n", correctPath);
    if (readFd == -1)
        return ;
    dup2(fd[0], STDIN_FILENO);
    dup2(readFd, STDOUT_FILENO);
    close(fd[0]);
    if (execve(correctPath, cmd, env) == -1)
    {
        printf("error execve");
    }
}

int main(int argc, char **argv, char **env)
{
    int fd[2];
    int myPid;
    // fd[0] - read
    // fd[1] - write
    if (argc == 5)
    {
        if (pipe(fd) == -1)
            printf("error pipe");
        myPid = fork();
        if (myPid == -1)
            printf("error pid");
        if (myPid == 0) 
            childProcess(fd, argv, env);
        parentProcess(fd, argv, env);
    }

}

