#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void forkTest() {
        puts("TESTE FORK:\n");
    
    pid_t pid;
    
    pid = fork(); //cria processo
    
    if(pid > 0) {
        printf(" Processo Pai PID: %d ", pid);
    }
    else {
        printf(" Processo Filho PID: %d ", pid);
    }
    puts("FIM");
}

void main()
{
    forkTest();
}

---------------------------
TESTE FORK:

 Processo Pai PID: 1632 FIM
 Processo Filho PID: 0 FIM

RUN FAILED (exit value 10, total time: 219ms)
---------------------------
TESTE FORK:

 Processo Pai PID: 5440 FIM
 Processo Filho PID: 0 FIM

RUN FAILED (exit value 10, total time: 109ms)
---------------------------
TESTE FORK:

 Processo Pai PID: 5440 FIM
 Processo Filho PID: 0 FIM

RUN FAILED (exit value 10, total time: 109ms)
---------------------------
TESTE FORK:

 Processo Pai PID: 3424 FIM
 Processo Filho PID: 0 FIM

RUN FAILED (exit value 10, total time: 79ms)
---------------------------