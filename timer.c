/* timer.c - Part 3
 * Same as Part 2, but a SIGALRM is requested every second and counted.
 * On CTRL-C (SIGINT) the program prints how many alarms occurred and
 * the total number of seconds it was executing, then exits.
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

volatile sig_atomic_t signal_received = 0; //global flag set by the SIGALRM handler
volatile sig_atomic_t alarm_count = 0;     //number of alarms delivered
time_t start_time;                         //time the program started

void handler(int signum)
{ //SIGALRM handler
  printf("Hello World!\n");
  alarm_count++;       //track the number of alarms delivered
  signal_received = 1; //tell main() the signal was delivered
}

void sigint_handler(int signum)
{ //SIGINT (CTRL-C) handler
  time_t end_time = time(NULL);
  printf("\nNumber of alarms: %d\n", (int)alarm_count);
  printf("Total time executed: %ld seconds\n", (long)(end_time - start_time));
  exit(0);
}

int main(int argc, char * argv[])
{
  setvbuf(stdout, NULL, _IONBF, 0); //unbuffered so output appears right away
  start_time = time(NULL);          //record when the program started
  signal(SIGALRM, handler);         //register handler to handle SIGALRM
  signal(SIGINT, sigint_handler);   //register handler to handle SIGINT (CTRL-C)
  while (1) {
    signal_received = 0;
    alarm(1); //Schedule the next SIGALRM for 1 second
    while (!signal_received); //busy wait until the handler has run
    printf("Turing was right!\n");
  }
  return 0; //never reached
}
