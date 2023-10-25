#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ     13

//Last input
#define SYMBOL1 'I'
#define SYMBOL2 'P'
#define SYMBOL3 'L'

int main()
{
    int shared_memory_id;
    key_t key;
    char *shm_begin, *s;

    key = 5670;

    if ((shared_memory_id = shmget(key, SHMSZ, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
    }

    if ((shm_begin = shmat(shared_memory_id, NULL, 0)) == (char *) -1) {
        perror("shmat");
    }

    s = shm_begin+1;
    *shm_begin = SYMBOL3;

    int number = 1;
    int count = 0;

    while(count < 4){
        if(*shm_begin == SYMBOL3){
            char input = (char)('0' + number);
            *s = input;
            s = s + 3;
            number = number + 2;
            *shm_begin = SYMBOL1;
            count = count + 1;
        }
    }
}
