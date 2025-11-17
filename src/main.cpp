#include <headers/TaskLogger.h>
#include <headers/TaskAbs.h>
#include <headers/TaskLateral.h>
#include <headers/Persistence.h>
#include <headers/TaskStatus.h>
#include <headers/InterruptChoque.h>
#include <headers/ToggleABSInterrupt.h>
#include <headers/TaskBox.h>
#include <headers/TaskChoque.h>


#include <headers/globals.h>
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

TaskHandle_t handleStatus;
TaskHandle_t handleAbs;
TaskHandle_t handleLateral;
TaskHandle_t handleLogger;
TaskHandle_t handleBox;
TaskHandle_t handleChoque;
void setup()
{
    // ## Pines ##
    // Acelerometros
    pinAcelerador = A0;
    pinFreno = A1;
    pinVolante = A2;

    // Botones
    pinSensorChoque = 2;
    pinToggleABS = 3;

    // Colores led
    pinRojo = 10;
    pinVerde = 9;
    Serial.begin(115200);
    EEPROM.begin();
    loadParameters();

    logQueue = xQueueCreate(20, sizeof(LogMessage));

    semChoqueDetectado = xSemaphoreCreateBinary();
    semABSToggle = xSemaphoreCreateBinary();

    mutexLedRGB = xSemaphoreCreateMutex();

    // Configurar pines
    pinMode(pinAcelerador, INPUT);
    pinMode(pinFreno, INPUT);
    pinMode(pinSensorChoque, INPUT);
    pinMode(pinToggleABS, INPUT);
    pinMode(pinRojo, OUTPUT);
    pinMode(pinVerde, OUTPUT);

    // Crear tareas
    xTaskCreate(taskBox, "Box", 512, NULL, 1, &handleBox);
    xTaskCreate(taskLogger, "Logger", 768, NULL, 2, &handleLogger);
    xTaskCreate(taskChoque, "Choque", 256, NULL, 3, &handleChoque);
    xTaskCreate(taskStatus, "Status", 256, NULL, 3, &handleStatus);
    xTaskCreate(taskABS, "ABS", 256, NULL, 2, &handleAbs);
    xTaskCreate(taskLateral, "Lateral", 256, NULL, 2, &handleLateral);

    //assignar interrupciones
    attachInterrupt(digitalPinToInterrupt(pinSensorChoque), interruptChoque, RISING);
    attachInterrupt(digitalPinToInterrupt(pinToggleABS), interruptToggleABS, RISING);


    if (logQueue == NULL || semChoqueDetectado == NULL ||
        semABSToggle == NULL || mutexLedRGB == NULL)
    {
        Serial.println("Error al crear la cola de logs");
        while (1)
            ;
    }

    // Iniciar el scheduler
    vTaskStartScheduler();
}
void loop()
{
}
