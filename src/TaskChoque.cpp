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
            LogMessage msg;
            snprintf(msg.message, sizeof(msg.message), "CHOQUE DETECTADO");
            enviar_log(msg.message);
        }
    }
}
