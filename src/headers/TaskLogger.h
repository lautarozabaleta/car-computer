#ifndef TASK_LOGGER_H
#define TASK_LOGGER_H
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>

// ============== FUNCIONES AUXILIARES ==============
void enviar_log(const char* formato, ...);

// ============== TAREA ==============
void taskLogger(void* parameter);

#endif 