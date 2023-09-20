#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>

bool globalvar = 0;


int signalHandler(){
    globalvar = 1;
}

int main(){
    int randomNumber = rand()%10;
    mkfifo("/tmp/myfifo", 0666);
    myfifo = open("/tmp/myfifo", O_RDWR);
    signal(SIGUSR1, signalHandler);
    while(1){
        sleep(1);
        if (globalvar){
            printf("Wrote on FIFO: %d\n", randomNumber);
            write(myfifo, &randomNumber, sizeof(int));
            sleep(1);
            int received_num;
            read(myfifo, &received_num, sizeof(int));
            printf("Read from FIFO: %d\n", received_num);
        }
    }
}