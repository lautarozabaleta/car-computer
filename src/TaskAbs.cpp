#include "headers/TaskAbs.h"
#include <headers/globals.h>
void calcAbs(float brakePercentage)
{
    float absForce = absLowerThreshold * pow((brakePercentage - absUpperThreshold) / (absUpperThreshold - absLowerThreshold), 2) * maxBrakeForce;
    effectiveBrakeForce = absForce;
    LogMessage msg;
    snprintf(msg.message, sizeof(msg.message), "ABS activado: Fuerza de frenado efectiva = %.2f N", effectiveBrakeForce);
    xQueueSend(logQueue, &msg, pdMS_TO_TICKS(100));
}
void taskABS(void *parameter)
{
    LogMessage msg;

    for (;;)
    {
        // Bloquearse esperando el semáforo del evento toggle ABS
        if (xSemaphoreTake(semABSToggle, pdMS_TO_TICKS(10)) == pdTRUE)
        {
            // Evento de toggle ABS recibido desde la interrupción
            absActivated = !absActivated;

            // Enviar mensaje de log
            snprintf(msg.message, sizeof(msg.message),
                     "ABS %s", absActivated ? "ACTIVADO" : "DESACTIVADO");
            xQueueSend(logQueue, &msg, pdMS_TO_TICKS(100));
        }

        // Continuar con la lógica normal de ABS si está activado
        float brakePercentage = analogRead(pinFreno) / 1023.0;
        if (!absActivated)
        {
            vTaskDelay(pdMS_TO_TICKS(50));
            continue;
        }

        if (brakePercentage > absUpperThreshold)
        {
            absWarningActive = true;
            calcAbs(brakePercentage);
        }
        else if (brakePercentage < absLowerThreshold)
        {
            effectiveBrakeForce = brakePercentage * maxBrakeForce;
            absWarningActive = false;
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
