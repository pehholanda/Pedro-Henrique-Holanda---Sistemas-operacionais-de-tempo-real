// Exemplo de uso de threads Posix em C no Linux
// Compilar com: gcc thread_exemplo.c -o thread_exemplo -lpthread
// Executar ./thread_exemplo
// (-lpthread é necessário para linkar a biblioteca de threads POSIX)

#include <pthread.h>   // funções de threads (pthread_create, pthread_exit, etc.)
#include <stdio.h>     // printf
#include <stdlib.h>    // exit, malloc, etc.
#include <unistd.h>    // sleep

#define NUM_THREADS 5  // define um número fixo de threads

// Função que cada thread criada vai executar
void *print_hello(void *threadid)
{
    // Mostra uma mensagem de início, identificando a thread
    printf("%ld: Hello World!\n", (long) threadid);

    // Simula um trabalho da thread: espera 5 segundos
    sleep(5);

    // Mostra uma mensagem final, após o "trabalho"
    printf("%ld: Bye bye World!\n", (long) threadid);

    // Encerra a execução da thread de forma limpa
    pthread_exit(NULL);
}
