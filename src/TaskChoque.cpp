#include "headers/TaskChoque.h"
#include <headers/globals.h>

void taskChoque(void *parameter)
{
    LogMessage msg;

    for (;;)
    {
        // Bloquearse esperando el semáforo del evento de choque
        if (xSemaphoreTake(semChoqueDetectado, portMAX_DELAY) == pdTRUE)
        {
            // Evento de choque recibido desde la interrupción
            crashed = true;

            // Enviar mensaje de log
            snprintf(msg.message, sizeof(msg.message), "CHOQUE DETECTADO");
            xQueueSend(logQueue, &msg, pdMS_TO_TICKS(100));
        }
    }
}
