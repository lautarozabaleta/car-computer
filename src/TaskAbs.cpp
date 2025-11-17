#include "headers/TaskAbs.h"
#include <headers/globals.h>
#include <headers/TaskLogger.h>

void calcAbs(float brakePercentage)
{
    float absForce = absLowerThreshold * pow((brakePercentage - absUpperThreshold) / (absUpperThreshold - absLowerThreshold), 2) * maxBrakeForce;
    effectiveBrakeForce = absForce;

    // Evitar loguear siempre
    int log = rand() % 10;
    if (log == 0)
    {
        LogMessage msg;
        char forceStr[10];
        dtostrf(effectiveBrakeForce, 6, 2, forceStr); // 6 ancho total, 2 decimales
        snprintf(msg.message, sizeof(msg.message), "ABS activado: Fuerza = %s N", forceStr);
        enviar_log(msg.message);
    }
}

// ============== TAREA ABS ==============
void taskABS(void *parameter)
{
    for (;;)
    {
        // Bloquearse esperando el semáforo del evento toggle ABS
        if (xSemaphoreTake(semABSToggle, pdMS_TO_TICKS(10)) == pdTRUE)
        {
            // Evento de toggle ABS recibido desde la interrupción
            absActivated = !absActivated;

            // Enviar mensaje de log
            LogMessage msg;
            snprintf(msg.message, sizeof(msg.message), "ABS %s", absActivated ? "ACTIVADO" : "DESACTIVADO");
            enviar_log(msg.message);
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
