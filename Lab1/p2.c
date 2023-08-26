//server signal handler
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void act(int s, siginfo_t *i, void *v){
    printf("Received %d\n", i->si_value.sival_int);
}

int main(int argc, char **argv){
    struct sigaction sa = {
        .sa_sigaction=act ,
        .sa_flags = SA_RESTART|SA_SIGINFO
    } ;
    sigaction(SIGUSR1, &sa, NULL);
    printf("%d\n", (int)getpid());
    for(;;){
        pause();
    }
}