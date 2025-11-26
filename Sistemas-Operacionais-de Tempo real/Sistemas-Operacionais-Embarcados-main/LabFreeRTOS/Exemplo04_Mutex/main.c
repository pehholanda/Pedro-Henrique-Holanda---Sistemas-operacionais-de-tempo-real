#include <stdio.h>
#include <unistd.h>   // usleep() no ambiente POSIX

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"   // necessário para mutex

/* =======================================================================
 * Exemplo 04 – Proteção de recurso compartilhado com Mutex
 * Demonstra como várias tarefas podem usar um mesmo recurso (printf)
 * sem interferência, garantindo exclusão mútua.
 * ======================================================================= */

SemaphoreHandle_t xMutex;  // handle global do mutex

/* ---------- Task que usa o recurso ---------- */
void vTaskPrint(void *pvParameters)
{
    const char *nome = (const char *) pvParameters;

    for (;;)
    {
        /* Tenta pegar o mutex (espera indefinidamente) */
        if (xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE)
        {
            /* Início da seção crítica */
            printf("[%s] entrou na seção crítica\n", nome);
            for (int i = 0; i < 3; i++)
            {
                printf("  [%s] imprimindo linha %d\n", nome, i + 1);
                vTaskDelay(pdMS_TO_TICKS(300)); // simula trabalho
            }
            printf("[%s] saindo da seção crítica\n\n", nome);
            /* Fim da seção crítica */

            /* Libera o mutex para que outras tasks possam usar */
            xSemaphoreGive(xMutex);
        }

        /* Espera um pouco antes de tentar novamente */
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/* =======================================================================
 * Hooks obrigatórios (mínimos para o port POSIX)
 * ======================================================================= */
void vApplicationMallocFailedHook(void)
{
    printf("ERRO: malloc falhou!\n");
    fflush(stdout);
    taskDISABLE_INTERRUPTS();
    for(;;);
}

void vAssertCalled(const char * const pcFileName, unsigned long ulLine)
{
    printf("ASSERT falhou em %s:%lu\n", pcFileName, ulLine);
    fflush(stdout);
    taskDISABLE_INTERRUPTS();
    for(;;);
}

void vApplicationTickHook(void) { }
void vApplicationIdleHook(void) { usleep(1000); }

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[configMINIMAL_STACK_SIZE];
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[configTIMER_TASK_STACK_DEPTH];
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

void vApplicationDaemonTaskStartupHook(void) { }

/* =======================================================================
 * Ponto de entrada
 * ======================================================================= */
int main(void)
{
    printf("=== FreeRTOS: Exemplo 04 – Mutex ===\n");

    /* Cria o mutex */
    xMutex = xSemaphoreCreateMutex();

    if (xMutex == NULL)
    {
        printf("Falha ao criar mutex!\n");
        return -1;
    }

    /* Cria três tarefas que compartilham o printf */
    xTaskCreate(vTaskPrint, "TaskA", 1024, "TaskA", 2, NULL);
    xTaskCreate(vTaskPrint, "TaskB", 1024, "TaskB", 2, NULL);
    xTaskCreate(vTaskPrint, "TaskC", 1024, "TaskC", 2, NULL);

    /* Inicia o escalonador */
    vTaskStartScheduler();

    for (;;); // nunca deve chegar aqui
}
