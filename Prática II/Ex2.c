######  2. Limite o Ciclo da função print_xs() a 10 repetições e o ciclo da função main() a 50. O que observa?

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>


/* Prints x’s to stderr. The parameter is unused. Does not return. */
void* print_xs (void* unused) {
    int valorXs = 10;
    while (valorXs != 0) {
    fputc ('x', stderr);
    valorXs --;
  }
  return NULL;
}

/* The main program. */
int main ()
{
  pthread_t thread_id;
  /* Create a new thread. The new thread will run the print_xs() function. */

  pthread_create (&thread_id, NULL, &print_xs, NULL);

  /* Print o’s continuously to stderr. */
  int valorMain = 50;
  while (valorMain) {
    fputc ('o', stderr);
    valorMain -- ;
  }

  return 0;
} 


###### E com o inverso? (print_xs() a 50 e o main() a 10) Que conclusões obtém?

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>


/* Prints x’s to stderr. The parameter is unused. Does not return. */
void* print_xs (void* unused) {
    int valorXs = 50;
    while (valorXs != 0) {
    fputc ('x', stderr);
    valorXs --;
  }
  return NULL;
}

/* The main program. */
int main ()
{
  pthread_t thread_id;
  /* Create a new thread. The new thread will run the print_xs() function. */

  pthread_create (&thread_id, NULL, &print_xs, NULL);

  /* Print o’s continuously to stderr. */
  int valorMain = 10;
  while (valorMain) {
    fputc ('o', stderr);
    valorMain -- ;
  }

  return 0;
}