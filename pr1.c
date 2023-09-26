#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int globalvar = 0;
int totalcounter = 0;
void signalHandler(int signo) {
    globalvar++;
    totalcounter++;
}

int main() {
    mkfifo("/tmp/myfifo1", 0666);
    mkfifo("/tmp/myfifo2", 0666);
    int myfifo1 = open("/tmp/myfifo1", O_RDWR);
    int myfifo2 = open("/tmp/myfifo2", O_RDWR);

    signal(SIGUSR2, signalHandler);
    
    while (1) {
        
        if (globalvar > 0) {
            printf("%d.-\n", globalvar);
            int randomNumber = rand() % 100;
            printf("Write on FIFO1: %d\n", randomNumber);
            write(myfifo1, &randomNumber, sizeof(int));

            sleep(1);

            int received_num;
            read(myfifo2, &received_num, sizeof(int));
            printf("Read from FIFO2: %d\n", received_num);

            globalvar--;
            printf("---------------------------------------------------------\n");
        }
    }

    close(myfifo1);
    close(myfifo2);

    return 0;
}