#include <headers/globals.h>
// Definición de variables globales accidentado
volatile bool crashed = false;
volatile bool absActivated = true;
volatile bool absWarningActive = false;

// ## Pines ##
// Acelerometros
int pinAcelerador = 0;
int pinFreno = 0;
int pinVolante = 0;

// Botones
int pinSensorChoque = 0;
int pinToggleABS = 0;

// Colores led
int pinRojo = 0;
int pinVerde = 0;

// Variables de parámetros del vehículo
float mass = 0.0f;
float maxPower = 0.0f;
float maxBrakeForce = 0.0f;
float lateralConstant = 0.0f;
float lateralAccelerationThreshold = 0.0f;
float absUpperThreshold = 0.0f;
float absLowerThreshold = 0.0f;
float effectiveBrakeForce = 0.0f;

// Variables de estado del vehículo
float currentSpeed = 0.0f;
float appliedThrottlePercentage = 0.0f;
float effectiveBrakePercentage = 0.0f;

QueueHandle_t logQueue = NULL;

// Semáforos binarios para eventos de interrupciones
SemaphoreHandle_t semChoqueDetectado = NULL;
SemaphoreHandle_t semABSToggle = NULL;

// Mutex para exclusión mutua del LED RGB
SemaphoreHandle_t mutexLedRGB = NULL;

