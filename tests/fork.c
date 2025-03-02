#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

// void child_process()
// {
//     execlp("ls", "ls", "-l", NULL);
// }
void *ft_malloc(size_t size, int flag);
int main()
{   
    ft_malloc(10, 0);
    ft_malloc(10, 0);   
    ft_malloc(10, 0);

    ft_malloc(10, 1);ft_malloc(10, 0);
    ft_malloc(10, 0);   
    ft_malloc(10, 0);

    ft_malloc(10, 1);
   
    return 0;
}