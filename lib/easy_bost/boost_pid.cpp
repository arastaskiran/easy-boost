#include <boost_pid.h>

BoostPID::BoostPID(double KP, double KI, double KD, double sample_ms, unsigned char min_pwm, unsigned char max_pwm)
{
    kp = KP;
    ki = KI;
    kd = KD;
    error = 0;
    set_point = 0;
    measured_value = 0;
    last_error = 0;
    integral = 0;
    derivative = 0;
    output = 0;
    sample_time = sample_ms;
    last_time = 0;
    min_p = min_pwm;
    max_p = max_pwm;
    pwmListener = 0;
    current_time = millis();
}

void BoostPID::setPoint(double val)
{
    set_point = val;
}

void BoostPID::syncVoltage(float val)
{
    measured_value = (double)val;
}

bool BoostPID::canISample()
{
    current_time = millis();
    return (current_time - last_time) >= sample_time;
}

int BoostPID::compute()
{
    if (!canISample())
    {
        return (int)output;
    }
    double delta = (current_time - last_time) / 1000.0;
    error = set_point - measured_value;
    integral += error * delta;
    derivative = (error - last_error) / delta;
    output = kp * error + ki * integral + kd * derivative;
    output = constrain(output, min_p, max_p);
    if (pwmListener != NULL)
    {
        pwmListener((int)output);
    }
    return (int)output;
}

void BoostPID::setPwmHandler(void (*listener)(int))
{
    pwmListener = listener;
}