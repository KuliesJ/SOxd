#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    int pipes1[2]; // Pipe para enviar x del padre al hijo
    int pipes2[2]; // Pipe para enviar x+1 del hijo al padre

    if (pipe(pipes1) == -1 || pipe(pipes2) == -1) {
        perror("Error al crear los pipes");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("Error al hacer fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Código del hijo
        close(pipes1[1]); // Cierra el extremo de escritura del primer pipe
        close(pipes2[0]); // Cierra el extremo de lectura del segundo pipe

        while (1) {
            int x;
            read(pipes1[0], &x, sizeof(int)); // Lee x del padre
            printf("Recibido %d desde padre a través de pipes1\n", x);

            // Incrementa x y envía de vuelta al padre
            x = x * 3;
            write(pipes2[1], &x, sizeof(int));
            printf("Enviado %d desde hijo a padre a través de pipes2\n", x);
        }

        close(pipes1[0]);
        close(pipes2[1]);
        exit(EXIT_SUCCESS);
    } else { // Código del padre
        close(pipes1[0]); // Cierra el extremo de lectura del primer pipe
        close(pipes2[1]); // Cierra el extremo de escritura del segundo pipe

        while (1) {
            // Lee un entero de la FIFO myfifo1
            int fd_fifo1 = open("/tmp/myfifo1", O_RDONLY);
            if (fd_fifo1 == -1) {
                perror("Error al abrir myfifo1");
                exit(EXIT_FAILURE);
            }

            int x;
            read(fd_fifo1, &x, sizeof(int));
            close(fd_fifo1);

            printf("Recibido %d desde myfifo1\n", x);
            x = x + 7;
            // Envía x al hijo a través del primer pipe
            write(pipes1[1], &x, sizeof(int));
            printf("Enviado %d desde padre a hijo a través de pipes1\n", x);

            // Espera a que el hijo envíe x+1 de vuelta
            int resultado;
            read(pipes2[0], &resultado, sizeof(int));
            printf("Recibido %d desde hijo a padre a través de pipes2\n", resultado);

            // Escribe el resultado en la FIFO myfifo2
            int fd_fifo2 = open("/tmp/myfifo2", O_WRONLY);
            if (fd_fifo2 == -1) {
                perror("Error al abrir myfifo2");
                exit(EXIT_FAILURE);
            }
            write(fd_fifo2, &resultado, sizeof(int));
            printf("Enviado %d desde padre a través de myfifo2\n", resultado);
            close(fd_fifo2);
            printf("---------------------------------------------------------\n");
        }

        close(pipes1[1]);
        close(pipes2[0]);
    }

    return 0;
}
