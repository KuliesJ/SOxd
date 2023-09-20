#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>

int myfifo;

void sigusr1_handler(int signo) 
{
    int randomNumber = rand() % 100;
    printf("Wrote on FIFO: %d\n", randomNumber);

    write(myfifo, &randomNumber, sizeof(int)); // Enviar número al FIFO
    sleep(1);
    int received_num;
    read(myfifo, &received_num, sizeof(int)); // Leer número desde el FIFO
    printf("Read from FIFO: %d\n", received_num);
}

int main()
{
    srand(time(NULL));
    mkfifo("/tmp/myfifo", 0666);
    myfifo = open("/tmp/myfifo", O_RDWR); // Abrir el FIFO para lectura y escritura
    signal(SIGUSR1, sigusr1_handler);

    while (1) 
    {
        sleep(1);
    }

    return 0;
}
