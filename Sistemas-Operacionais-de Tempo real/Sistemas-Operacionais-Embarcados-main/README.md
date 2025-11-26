# Sistemas-Operacionais-Embarcados e Sistemas de Tempo Real

Laboratório Prático – Sistemas Operacionais Embarcados e Sistemas de Tempo Real (Linux)

-----------------------------------------------------------------------------------

🔧 Ambiente

Linux nativo ou em máquina virtual (Ubuntu/Debian recomendados).

Compilador GCC.

Editor de texto (nano, vim, VS Code).

Terminal Linux.

-----------------------------------------------------------------------------------

Experimento 1 – Primeira chamada de sistema

Objetivo: Entender chamadas de sistema básicas (write, _exit).

Código: hello_syscall.c

gcc hello_syscall.c -o hello

./hello

Esperado: mensagem Hello World! no terminal.

-----------------------------------------------------------------------------------

Experimento 2 – Criação de processos com fork

Objetivo: Mostrar como o Linux cria novos processos.

Código: fork_example.c

gcc fork_example.c -o fork_example

./fork_example

Esperado: duas mensagens, uma do pai e outra do filho.

-----------------------------------------------------------------------------------

Experimento 3 – Comunicação entre processos (pipe)

Objetivo: Demonstrar IPC (Inter-Process Communication).

Código: pipe_example.c

gcc pipe_example.c -o pipe_example

./pipe_example

Esperado: o pai imprime a mensagem enviada pelo filho.


-----------------------------------------------------------------------------------


Experimento 4 – Sincronização com Semáforos

Objetivo: Controlar acesso simultâneo a recursos compartilhados.

Código: semaphore_example.c

gcc semaphore_example.c -o semaphore_example -lpthread

./semaphore_example

Esperado: execução ordenada das threads sem conflito.


-----------------------------------------------------------------------------------


Experimento 5 – Tratando sinais (Ctrl+C)

Objetivo: Simular interrupções no espaço do usuário.

Código: signal_example.c

gcc signal_example.c -o signal_example

./signal_example

Esperado: ao pressionar Ctrl+C, não encerra o programa imediatamente, mas exibe mensagem de captura do sinal.


-----------------------------------------------------------------------------------


Experimento 6 – Preempção por fatia de tempo (SCHED_OTHER)

Objetivo: Mostrar que, no escalonador padrão do Linux (CFS/SCHED_OTHER), mesmo sem cooperação (sleep ou yield), o kernel força a troca de CPU entre threads por time slice.

Código: preempt_timeslice.c

gcc preempt_timeslice.c -o preempt_timeslice -lpthread

./preempt_timeslice

Esperado: Dois contadores (t1 e t2) crescem ao mesmo tempo, porque o kernel divide a CPU entre eles de forma preemptiva.

-----------------------------------------------------------------------------------

Experimento 7 – Tempo real (SCHED_FIFO) e fome de CPU (starvation)

Objetivo: Demonstrar que processos em tempo real (SCHED_FIFO) podem monopolizar a CPU e causar starvation em processos normais.

Código: rt_starvation.c

gcc rt_starvation.c -o rt_starvation

sudo taskset -c 0 ./rt_starvation

Esperado: O filho em tempo real imprime mensagens continuamente e ocupa a CPU. O pai, rodando em SCHED_OTHER, quase não consegue imprimir porque sofre starvation.

Dica: se o pai ainda imprimir com frequência, é por causa do RT throttling do kernel (reserva ~5% do tempo do core para tarefas não-RT).

-----------------------------------------------------------------------------------

Experimento 8 – Prioridade dinâmica com nice (SCHED_OTHER)

Objetivo: Mostrar que no escalonador CFS (SCHED_OTHER) todos os processos continuam preemptivos, mas a distribuição da CPU depende da prioridade dinâmica (nice).

Código: nice_demo.c

gcc nice_demo.c -o nice_demo

sudo ./nice_demo

Esperado: O processo com nice=-5 incrementa seu contador mais rápido, enquanto o com nice=+15 progride mais devagar. Ambos continuam rodando, mas com fatias de CPU desbalanceadas conforme a prioridade.




