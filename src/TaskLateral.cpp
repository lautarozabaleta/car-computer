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
    currentSpeed = speed;
    appliedThrottlePercentage = throttlePercentage;
    effectiveBrakePercentage = effectiveBrakeForce / maxBrakeForce;
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
            LogMessage msg;
            char accelStr[10];
            dtostrf(lateralAcceleration, 6, 2, accelStr);
            snprintf(msg.message, sizeof(msg.message), "Alerta de riesgo lateral: %s m/s2", accelStr);
            enviar_log(msg.message);
        }

        if (lateralAcceleration > lateralAccelerationThreshold * 1.5f)
        {
            crashed = true;
            LogMessage msg;
            snprintf(msg.message, sizeof(msg.message), "COLISION LATERAL");
            enviar_log(msg.message);
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}