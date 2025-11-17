#include "headers/TaskLogger.h"
#include <headers/globals.h>

// ============== FUNCIONES AUXILIARES ==============
void enviar_log(const char* mensaje, ...) {
    if (logQueue == NULL) return;
    LogMessage msg;
    snprintf(msg.message, sizeof(msg.message), mensaje);
    msg.tiempo = xTaskGetTickCount();
    xQueueSend(logQueue, &msg, pdMS_TO_TICKS(10));
}

// ============== TAREA LOGGER ==============
void taskLogger(void *parameter)
{
    LogMessage msg;
    for (;;)
    {
        if (xQueueReceive(logQueue, &msg, pdMS_TO_TICKS(100)) == pdTRUE)
        {
            Serial.print(F("["));
            Serial.print(msg.tiempo);
            Serial.print(F("] "));
            Serial.println(msg.message);
        }
    }
}