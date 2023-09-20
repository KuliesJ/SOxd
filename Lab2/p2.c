#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_BUF 1024

int main() 
{
    mkfifo("/tmp/myfifo", 0666);
    char buf[MAX_BUF];
    
    int result_fd;
    result_fd = open("/tmp/myfifo", O_WRONLY); // Abrir el FIFO para escritura

    while (1) 
    {
        sleep(2);
        int fd1;
        if ((fd1 = open("/tmp/myfifo", O_RDONLY)) < 0) {
            perror("Error al abrir el pipe");
            exit(1);
        }
        
        read(fd1, buf, sizeof(int));
        close(fd1);
        
        int num = *((int*)buf);
        int received = num + 7;
        printf("p1 -> p2: %d\n", received);

        int result_son;

        int fd[2], nbytes;
        pipe(fd);
        pid_t childpid;
        
        childpid = fork();
        
        if (childpid == 0)
        {
            sleep(1);
            result_son = received * 3;
            printf("p2 (hijo) -> p1: %d\n", result_son);
            
            close(fd[0]);
            write(fd[1], &result_son, sizeof(int));
            
            exit(0);
        }
        else
        {
            sleep(1);
            close(fd[1]);
            nbytes = read(fd[0], &result_son, sizeof(int)); 
            int result_final = result_son + 7;
            printf("p2 -> p1: %d\n\n", result_final);
            
            // Enviar el resultado de vuelta a p1 a través del FIFO
            write(result_fd, &result_final, sizeof(int));
        }
    }
    
    return 0;
}