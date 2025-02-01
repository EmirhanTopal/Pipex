#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    int fd[2];
    // fd[0] - read
    // fd[1] - write

    if(pipe(fd) == -1)
    {
        printf("an error");
        return 1;
    }
    int id = fork();
    if (id == 0)
    {
        close(fd[0]);
        int x = 4;
        printf("%d", x);
        write(fd[1], &x, sizeof(int));
        close(fd[1]);
    }
    return 0;
}