#include <headers/TaskStatus.h>
#include <headers/globals.h>

// ============== FUNCIONES AUXILIARES ==============
void setLedColor(uint8_t rojo, uint8_t verde)
{
    if (xSemaphoreTake(mutexLedRGB, portMAX_DELAY) == pdTRUE)
    {
        analogWrite(pinRojo, rojo);
        analogWrite(pinVerde, verde);
        xSemaphoreGive(mutexLedRGB);
    }
}

void yellowLed()
{
    setLedColor(255, 80);
}

void orangeLed()
{
    setLedColor(255, 20);
}

void greenLed()
{
    setLedColor(0, 255);
}

void redLed()
{
    setLedColor(255, 0);
}

void apagarLed()
{
    setLedColor(0, 0);
}

// ============== TAREA STATUS/LED ==============
void taskStatus(void *parameter)
{
    for (;;)
    { // Loop infinito obligatorio
        if (crashed)
        {
            redLed();
        }
        else if (absWarningActive)
        {
            orangeLed();
        }
        else if (!absActivated)
        {
            yellowLed();
        }
        else
        {
            greenLed();
        }
        vTaskDelay(pdMS_TO_TICKS(500));
        apagarLed();
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
