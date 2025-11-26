/*
 * Experimento 3: Prioridade dinâmica com nice (SCHED_OTHER / CFS)
 *
 * Objetivo:
 *   Mostrar que, sob o escalonador padrão do Linux (CFS), a CPU é preemptiva
 *   entre tarefas "normais" (SCHED_OTHER), mas a distribuição das fatias (tempo
 *   de CPU) é influenciada pela prioridade dinâmica "nice".
 *
 * Conceitos:
 *   - nice alto  (ex.: +15)  => pior prioridade (recebe MENOS CPU)
 *   - nice baixo (ex.:  -5)  => melhor prioridade (recebe MAIS CPU)
 *   - Ambos continuam preemptáveis, mas não igualmente favorecidos.
 *
 * Observação:
 *   - Para usar valores de nice NEGATIVOS, geralmente é preciso rodar como root
 *     (sudo) ou ter a capacidade CAP_SYS_NICE.
 *
 *  Como compilar e executar:
 *   gcc nice_demo.c -o nice_demo
 *   sudo ./nice_demo    # sudo ajuda a aplicar nice negativo (-5)
 *
 *   Dica opcional para isolar a observação em 1 core:
 *      sudo taskset -c 0 ./nice_demo
 */

#include <stdio.h>          // printf, fflush
#include <unistd.h>         // fork, _exit
#include <sys/resource.h>   // setpriority (altera nice)
#include <sys/wait.h>       // wait
#include <time.h>           // nanosleep

// Função "trabalho" de cada filho: CPU-bound que incrementa um contador.
// A cada 200 ms, imprime o valor atual do contador.
// NOTA: o nanosleep aqui é só para tornar a demonstração legível (tempo de observação);
//       o avanço do contador reflete quanto de CPU cada processo está recebendo.
void loop_contador(const char* name) {
    volatile unsigned long long c = 0;

    for (int i = 0; i < 20; i++) {
        // Simula uso contínuo de CPU entre impressões
        struct timespec ts = { .tv_sec = 0, .tv_nsec = 200 * 1000 * 1000 }; // 200 ms
        nanosleep(&ts, NULL);

        printf("%s: %llu\n", name, c);
        fflush(stdout);

        // Trabalha (consome CPU) entre as impressões
        // (um "busy loop" simples)
        for (unsigned long k = 0; k < 50ULL * 1000ULL * 1000ULL; k++) {
            c++;
        }
    }
    _exit(0);
}

int main() {
    // Cria o primeiro filho (vai ter pior prioridade: nice=+15)
    pid_t p1 = fork();
    if (p1 == 0) {
        // setpriority: valores positivos => pior prioridade
        // Retorno 0 = sucesso; -1 = erro (checar permissões)
        if (setpriority(PRIO_PROCESS, 0, 15) != 0) {
            perror("setpriority filho nice=15");
        }
        loop_contador("nice=+15");
    }

    // Cria o segundo filho (melhor prioridade: nice=-5)
    pid_t p2 = fork();
    if (p2 == 0) {
        // Valores negativos => melhor prioridade (pode exigir sudo/CAP_SYS_NICE)
        if (setpriority(PRIO_PROCESS, 0, -5) != 0) {
            perror("setpriority filho nice=-5 (tente sudo)");
        }
        loop_contador("nice=-5");
    }

    // Processo pai: apenas espera os dois filhos terminarem
    wait(NULL);
    wait(NULL);
    return 0;
}
