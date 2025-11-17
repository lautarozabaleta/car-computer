#include "headers/InterruptChoque.h"
#include <headers/globals.h>
void interruptChoque()
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    // Despertar tarea enviando señal por semáforo
    xSemaphoreGiveFromISR(semChoqueDetectado, &xHigherPriorityTaskWoken);

    // Forzar cambio de contexto si hay una tarea de mayor prioridad lista
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}