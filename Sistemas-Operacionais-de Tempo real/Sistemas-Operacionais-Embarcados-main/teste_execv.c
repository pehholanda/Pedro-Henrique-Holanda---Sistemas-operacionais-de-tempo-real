//
// gcc teste_execv.c -o teste_execv
// ./teste_execv


#include <stdio.h>
#include <unistd.h>   // execv, getpid

int main(void)
{
    // Mostra o PID do processo antes da troca
    printf("pid do Pai (processo atual): %d\n", getpid());

    // Substitui o processo atual pelo executável "teste"
    //  1º argumento: caminho do binário a ser executado
    //  2º argumento: vetor de argumentos (argv),
    //                precisa terminar em NULL
    char *args[] = {"teste", NULL};
    execv("./teste", args);

    // Se execv for bem-sucedido, NUNCA chega aqui
    // pois o processo foi substituído pelo programa "teste".
    // Esse printf só aparece se houver erro no execv.
    printf("EU TENHO UM SEGREDO PRA CONTAR\n");

    return 0;
}
