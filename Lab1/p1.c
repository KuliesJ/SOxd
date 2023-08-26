#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
pid_t pid;
int x = 66;

void signalHandler(int){
   int randomNumber = rand()%100;
   x += randomNumber;
   printf("Sending signal with %d value\n",x);
   union sigval val = {.sival_int = x};
   if (sigqueue(pid,SIGUSR1,val)==0){
   	printf("Sent\n");
   }
   else{
      printf("Not sent\n");
   }
}


int main(int argc, char **argv){
   pid = atoi(argv[1]);
   signal(SIGINT,signalHandler);
   while(1){
      sleep(3);
   }
   return 0;
}