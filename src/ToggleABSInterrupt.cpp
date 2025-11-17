#include "headers/ToggleABSInterrupt.h"
#include <headers/globals.h>

#define DEBOUNCE_DELAY_MS 200 // 200ms de debounce

// ============== INTERRUPCIÓN ==============
void interruptToggleABS()
{
    static TickType_t lastInterruptTime = 0;
    TickType_t interruptTime = xTaskGetTickCountFromISR();

    // Ignorar si han pasado menos de DEBOUNCE_DELAY_MS desde la última interrupción
    if ((interruptTime - lastInterruptTime) < pdMS_TO_TICKS(DEBOUNCE_DELAY_MS))
    {
        return;
    }

    lastInterruptTime = interruptTime;

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    // Despertar tarea enviando señal por semáforo
    xSemaphoreGiveFromISR(semABSToggle, &xHigherPriorityTaskWoken);

    // Forzar cambio de contexto si hay una tarea de mayor prioridad lista
    if (xHigherPriorityTaskWoken == pdTRUE)
    {
        portYIELD_FROM_ISR();
    }
}