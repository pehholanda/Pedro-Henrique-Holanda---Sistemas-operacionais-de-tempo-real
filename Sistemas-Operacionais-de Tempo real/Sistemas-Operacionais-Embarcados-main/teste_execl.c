//
// gcc teste_execl.c -o teste_execl
// ./teste_execl


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // fork, exec
#include <sys/types.h>

int main(void) {
    printf("PID do Pai: %d\n", getpid());

    pid_t pid = fork();

    if (pid == 0) {
        // Processo Filho
        execl("./teste", "teste", NULL);
        perror("exec falhou");
        exit(1);
    } else if (pid > 0) {
        // Processo Pai NÃO espera o filho
        printf("[PAI] Continuei sem esperar o filho!\n");
    } else {
        perror("fork falhou");
    }

    return 0;
}



