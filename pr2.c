#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int result_fd = open("/tmp/myfifo", O_WRONLY);
#define MAX_BUF 1024
int main(){
    char buf[MAX_BUF];
    
    //Pipes for coms dad/son
    int fd[2];
    //0 Read 
    //1 Write
    pipe(fd);

    while(1){
        //Forking
        pid_t childpid;
        childpid = fork();
        if(childpid < 0){
            perror("Pipe existencen't");
        }
        if(childpid == 0){
            //Hijo
            int result_son;
            read(fd[0], buf, sizeof(int));
            //
            write(fd[1],buf,sizeof(int));
        }
        if(childpid > 0){
            //Padre
            int fd1, nbytes;
            if ((fd1 = open("/tmp/myfifo", O_RDONLY)) < 0) {
                perror("Pipe existencen't");
                exit(1);
            }
            //Read from FIFO
            read(fd1, buf, sizeof(int));
            int num = *((int*)buf);
            //Write to FD1//hijo
            write(fd[0], &num, sizeof(int));
            sleep(2);
            //Read from FD2//hijo
            read(fd[1], buf, sizeof(int))
            //Write to FIFO
            sleep(1);
            nbytes = read(fd[0], &result_son, sizeof(int)); 
            int result_final = result_son + 7;
            printf("Wrote on FIFO: %d\n\n", result_final);
            write(result_fd, &result_final, sizeof(int));
        }
    }
    
    
}