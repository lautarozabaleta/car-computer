#include <headers/globals.h>
#include <headers/TaskLogger.h>
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

// ============== TAREA BOX (TELEMETRÍA) ==============
void taskBox(void *parameter)
{
    for (;;)
    {
        LogMessage msg;

        // Convertir floats a strings
        char speedStr[10];
        char accelStr[10];
        char brakeStr[10];

        dtostrf(currentSpeed, 6, 2, speedStr);
        dtostrf(appliedThrottlePercentage * 100.0, 5, 1, accelStr);
        dtostrf(effectiveBrakePercentage * 100.0, 5, 1, brakeStr);

        snprintf(msg.message, sizeof(msg.message),
                 "Estado - Vel: %s m/s | Acelerador: %s%% | Freno: %s%%",
                 speedStr, accelStr, brakeStr);

        enviar_log(msg.message);

        vTaskDelay(pdMS_TO_TICKS(350));
    }
}