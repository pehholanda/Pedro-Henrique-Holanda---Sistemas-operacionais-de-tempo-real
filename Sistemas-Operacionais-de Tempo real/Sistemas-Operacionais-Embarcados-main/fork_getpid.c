
//  Demonstra multitarefa e o gerenciamento de processos.
//  gcc fork_getpid.c -o fork_getpid
//  ./fork_getpid

#include <stdio.h>      // printf, scanf
#include <stdlib.h>     // exit
#include <sys/types.h>  // definição do tipo pid_t
#include <unistd.h>     // fork(), getpid()

int main(void) {
    int i;          // variável auxiliar para scanf (mantém processo aberto)
    pid_t pid;      // identificador de processo (PID)

    // Cria um novo processo (fork)
    // - Retorna < 0 se houve erro
    // - Retorna 0 no processo FILHO
    // - Retorna PID do filho no processo PAI
    if ((pid = fork()) < 0)
    {
        perror("fork");   // imprime mensagem de erro se falhar
        exit(1);          // encerra o programa
    }

    if (pid == 0)
    {
        // Este trecho é executado pelo processo FILHO
        printf("pid do Filho: %d\n", getpid()); // getpid() retorna o PID do processo atual
    }
    else
    {
        // Este trecho é executado pelo processo PAI
        printf("pid do Pai: %d\n", getpid());
    }

    // Esta parte do código será executada por AMBOS (pai e filho)
    printf("Esta regiao sera executada por ambos processos\n\n");

    // scanf é usado aqui apenas para "segurar" o programa aberto
    // Assim podemos observar a execução e os PIDs no terminal
    scanf("%d", &i);

    exit(0);  // encerra o processo (pai ou filho)
}
