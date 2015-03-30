#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

struct PCB {
  int pid;
  int n_inst;
  int time;
};

struct Process_Table {
  struct PCB *tbl[100]; /* máximo de 100 processos, para já */
  int size;
}
  PROCTBL, PROCQUEUE;

void PT_init(struct Process_Table *pt)
{
  pt->size = 0;
}

void PT_insert(struct Process_Table *pt, struct PCB *pcb)
{
  int i;
  for (i = pt->size; i > 0; i--) {
    pt->tbl[i] = pt->tbl[i-1];
  }
  pt->tbl[0] = pcb;
  pt->size++;
}

void PT_append(struct Process_Table *pt, struct PCB *pcb)
{
  pt->tbl[pt->size++] = pcb;
}

void PT_remove(struct Process_Table *pt, int pid)
{
  int i, found = -1;
  
  for (i = 0; i < pt->size; i++) {
    if (pid == pt->tbl[i]->pid) { /* found! */
      found = i;
    }
  }

  if (found == -1) return;
  
  /* mover todos uma "casa" para trás */
  for (i = found; i < pt->size-1; i++) {
    pt->tbl[i] = pt->tbl[i+1];
  }

  pt->size--;
}

struct PCB *PT_pop(struct Process_Table *pt)
{
  struct PCB *pcb = pt->tbl[0];
  int pid = pcb->pid;

  PT_remove(pt, pid);

  return pcb;
}

int PT_empty(struct Process_Table pt)
{
  return (pt.size == 0);
}
  
void load_input(char *path)
{
  FILE *fp = fopen(path, "r");
  int initime, n_inst;
  int currpid = 1;
  
  while(fscanf(fp, "%d %d\n", &initime, &n_inst) != EOF) {
    struct PCB *pcb = (struct PCB *) malloc (sizeof (struct PCB));

    pcb->pid    = currpid++;
    pcb->n_inst = n_inst;
    pcb->time   = initime;

    PT_append(&PROCQUEUE, pcb);
  }  
}

void exec_process(struct PCB *pcb, int time)
{
  printf("%d %d\n", time, pcb->pid);
  pcb->n_inst--;
}

void run_scheduler(int realtime)
{
  int TIME = 0;
  
  while (!PT_empty(PROCQUEUE) || !PT_empty(PROCTBL)) {
    /* meter os processos a começar neste instante no início da fila */
    while (!PT_empty(PROCQUEUE) && PROCQUEUE.tbl[0]->time <= TIME) {
      PT_insert(&PROCTBL, PROCQUEUE.tbl[0]);
      /* remover da lista de espera */
      PT_remove(&PROCQUEUE, PROCQUEUE.tbl[0]->pid);
    }

    if (!PT_empty(PROCTBL)) {
      struct PCB *pcb = PT_pop(&PROCTBL);
      exec_process(pcb, TIME);
      if (pcb->n_inst > 0) {
	PT_append(&PROCTBL, pcb);
      }
    }
    else {
      printf("%d NULL\n", TIME);
    }

    if (realtime) usleep(500000);
    
    TIME++;
  }
}

int main(int argc, char *argv[])
{
  PT_init(&PROCTBL);
  PT_init(&PROCQUEUE);

  if (argc > 1) {
    load_input(argv[1]);
  }
  else {
    load_input("input1");
  }

  run_scheduler(0);

  printf("\nbye!\n");
  
}
