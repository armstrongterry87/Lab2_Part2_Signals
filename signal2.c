/* signal2.c - Part 2
 * Every 5 seconds: "Hello World!" prints from the SIGALRM handler,
 * then "Turing was right!" prints from main(), forever.
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t signal_received = 0; //global flag set by the handler

void handler(int signum)
{ //signal handler
  printf("Hello World!\n");
  signal_received = 1; //tell main() the signal was delivered
}

int main(int argc, char * argv[])
{
  setvbuf(stdout, NULL, _IONBF, 0); //unbuffered so output appears right away
  signal(SIGALRM, handler); //register handler to handle SIGALRM
  while (1) {
    signal_received = 0;
    alarm(5); //Schedule the next SIGALRM for 5 seconds
    while (!signal_received); //busy wait until the handler has run
    printf("Turing was right!\n");
  }
  return 0; //never reached
}
