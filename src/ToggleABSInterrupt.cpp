#include "headers/ToggleABSInterrupt.h"
#include <headers/globals.h>
void interruptToggleABS()
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    // Despertar tarea enviando señal por semáforo
    xSemaphoreGiveFromISR(semABSToggle, &xHigherPriorityTaskWoken);

    // Forzar cambio de contexto si hay una tarea de mayor prioridad lista
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}