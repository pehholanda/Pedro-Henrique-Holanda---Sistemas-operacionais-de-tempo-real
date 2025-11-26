

//
// gcc teste.c -o teste
// ./teste

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    // Apenas imprime o PID do processo que está rodando esse programa
    printf("\nPid do arquivo 'teste': %d\n", getpid());
    return 0;
}
