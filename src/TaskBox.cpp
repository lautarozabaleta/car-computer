#include <headers/globals.h>
#include <headers/TaskLogger.h>
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

// ============== TAREA BOX (TELEMETRÍA) ==============
void taskBox(void *parameter)
{
    for (;;)
    {
        enviar_log("Estado - Vel: %.2f m/s | Acel: %.1f%% | Freno: %.1f%%",
                   currentSpeed,
                   appliedThrottlePercentage * 100.0f,
                   effectiveBrakePercentage * 100.0f);

        vTaskDelay(pdMS_TO_TICKS(350));
    }
}