#include "headers/TaskAbs.h"
#include <headers/globals.h>
#include <headers/TaskLogger.h>

void calcAbs(float brakePercentage)
{
    float absForce = absLowerThreshold * pow((brakePercentage - absUpperThreshold) / (absUpperThreshold - absLowerThreshold), 2) * maxBrakeForce;
    effectiveBrakeForce = absForce;
    enviar_log("ABS activado: Fuerza de frenado efectiva = %.2f N", effectiveBrakeForce);
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
            enviar_log("ABS %s", absActivated ? "ACTIVADO" : "DESACTIVADO");
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
