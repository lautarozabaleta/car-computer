#include "headers/TaskLateral.h"
#include <headers/globals.h>
#include <headers/TaskLogger.h>

const float dt = 0.01f; // Intervalo de tiempo en segundos
float previousSpeed = 0.1f;
float calcSpeed()
{
    // Leer valor del acelerador y convertir a velocidad
    int aceleradorValue = analogRead(pinAcelerador);
    float throttlePercentage = aceleradorValue / 1023.0f;
    float ThrottlePower = throttlePercentage * maxPower;
    float ThrottleForce = ThrottlePower / previousSpeed;
    float acceleration = (ThrottleForce - effectiveBrakeForce) / mass;
    float speed = previousSpeed + acceleration * dt;
    if (speed < 0)
        speed = 0.0f;
    previousSpeed = speed;
    return speed;
}

float calcLateralAcceleration(float speed, float steeringAngle)
{
    return lateralConstant * speed * steeringAngle;
}

// ============== TAREA LATERAL ==============
void taskLateral(void *parameter)
{
    for (;;)
    {
        float steeringAngle = analogRead(pinVolante);
        steeringAngle = map(steeringAngle, 0, 1023, -90, 90);
        // Convierto a valor absoluto
        if (steeringAngle < 0)
            steeringAngle = -steeringAngle;
        float speed = calcSpeed();
        float lateralAcceleration = calcLateralAcceleration(speed, steeringAngle);

        if (lateralAcceleration > lateralAccelerationThreshold)
        {
            enviar_log("Alerta de riesgo lateral: %.2f m/s²", lateralAcceleration);
        }

        if (lateralAcceleration > lateralAccelerationThreshold * 1.5f)
        {
            crashed = true;
            enviar_log("COLISION LATERAL");
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}