#include "headers/TaskChoque.h"
#include <headers/globals.h>
#include <headers/TaskLogger.h>

// ============== TAREA CHOQUE ==============
void taskChoque(void *parameter)
{
    for (;;)
    {
        // Bloquearse esperando el semáforo del evento de choque
        if (xSemaphoreTake(semChoqueDetectado, portMAX_DELAY) == pdTRUE)
        {
            // Evento de choque recibido desde la interrupción
            crashed = true;

            // Enviar mensaje de log
            enviar_log("CHOQUE DETECTADO");
        }
    }
}
