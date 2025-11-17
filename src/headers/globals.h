#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <semphr.h>
#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H
// Variables globales accidentado
extern volatile bool crashed;
extern volatile bool absActivated;
extern volatile bool absWarningActive;

// ## Pines ##
// Acelerometros
extern int pinAcelerador;
extern int pinFreno;
extern int pinVolante;

// Botones
extern int pinSensorChoque;
extern int pinToggleABS;

// Colores led
extern int pinRojo;
extern int pinVerde;

// Variables de parámetros del vehículo
extern float mass;                         // Kg
extern float maxPower;                     // Watts
extern float maxBrakeForce;                // N
extern float lateralConstant;              // 1/(rad · s)
extern float lateralAccelerationThreshold; // m/s²
extern float absUpperThreshold;            // %
extern float absLowerThreshold;            // %
extern float effectiveBrakeForce;          // N

// Variables de estado del vehículo
extern float currentSpeed;                 // m/s
extern float appliedThrottlePercentage;    // 0.0 - 1.0
extern float effectiveBrakePercentage;     // 0.0 - 1.0

// Cola de mensajes para el logger
extern QueueHandle_t logQueue;

// Semáforos binarios para eventos de interrupciones
extern SemaphoreHandle_t semChoqueDetectado;
extern SemaphoreHandle_t semABSToggle;

// Mutex para exclusión mutua del LED RGB
extern SemaphoreHandle_t mutexLedRGB;

#define LOG_MESSAGE_SIZE 60
typedef struct
{
    char message[LOG_MESSAGE_SIZE];
    TickType_t tiempo;
} LogMessage;

#endif