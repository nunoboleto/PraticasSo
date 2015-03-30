#!/usr/bin/python3

import time
import sys

class scheduler4:
    def __init__(self, realtime=False):
        self.proctbl   = []
        self.procqueue = []
        self.time      = 0
        self.realtime  = realtime

    def add_process(self, time, ncpu):
        nproc = len(self.procqueue) + 1
        self.procqueue.append((time, ncpu, nproc))

    def start(self):
        self.proctbl.sort()
        self.procqueue.sort()

        while self.proctbl or self.procqueue:
            to_enter = [(t,n,p) for (t,n,p) in self.procqueue if t <= self.time]

            if to_enter:
                self.proctbl = to_enter + self.proctbl
                for X in to_enter:
                    self.procqueue.remove(X)

            if len(self.proctbl):
                t, n, p = self.proctbl.pop(0)
            else:
                n = None

            if n:
                print('%d %d' % (self.time, p))
                n -= 1
            else:
                print('%d NULL' % (self.time))

            if n: # se ainda tem instrucoes depois de decrementar
                self.proctbl.append((t,n,p)) # mover para o fim (round-robin...)

            if self.realtime:
                time.sleep(0.5)
                
            self.time += 1

    def load_file(self, path, clear=True):
        if clear:
            self.proctbl = []
            
        f = open(path)

        for line in f:
            l = line.strip()
            if l:
                try:
                    t, n = l.split()
                    self.add_process(int(t), int(n))
                except: # invalid line, skip
                    continue
                
        f.close()

        
        
if __name__ == '__main__':
    if len(sys.argv) > 1:
        path = sys.argv[1]
    else:
        path = 'input1'

    if len(sys.argv) > 2 and sys.argv[2] == 'nort':
        rt = False
    else:
        rt = True

    S = scheduler4(realtime=rt)
    S.load_file(path)
    S.start()

    print('\nbye!')
