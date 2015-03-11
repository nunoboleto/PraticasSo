#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

int main () {
    
    int i;
    double x;
    double y;
    
    for(i = 1; i <= 100; i++){

        x = sqrt(i);        
        y += x;
    }
    printf("total = %f\n", y);
    return(0);
  }