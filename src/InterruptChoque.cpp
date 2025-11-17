#include "headers/InterruptChoque.h"
#include <headers/globals.h>

// ============== INTERRUPCIÓN ==============
void interruptChoque()
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    // Despertar tarea enviando señal por semáforo
    xSemaphoreGiveFromISR(semChoqueDetectado, &xHigherPriorityTaskWoken);

    // Forzar cambio de contexto si hay una tarea de mayor prioridad lista
    if (xHigherPriorityTaskWoken == pdTRUE)
    {
        portYIELD_FROM_ISR();
    }
}