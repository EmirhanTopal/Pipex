#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    int fileIn = open("test.txt", O_RDONLY);
    if (fileIn == -1)
    {
        perror("Dosya açılamadı");
        return 1;
    }
    int file = open("dupTest.txt", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (file == -1)
    {
        return 3234;
    }
    printf("the fd to dupTest: %d\n", file);
    dup2(file, STDOUT_FILENO); // 1;
    dup2(fileIn, STDIN_FILENO);
    close(file);

    char cmd[] = "/usr/bin/cat"; // string array 
    char *argVec[] = {"cat", NULL};
    char *envVec[] = {NULL}; //pointer array
    printf("Start of execve call %s:\n", cmd);
    printf("--------------------------------------------\n");
    int i = 0;
    if (execve(cmd, argVec, envVec) == -1)
    {
        perror("gg");
    }
    printf("Oops kral orda dur");
}