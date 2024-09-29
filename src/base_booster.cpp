#include <base_booster.h>

BaseBooster::BaseBooster()
{
    pwm_pin = 0;
}

void BaseBooster::setSourceVoltmeter(uint8_t pin, float r1, float r2)
{
    source_meter = new RustyVoltmeter(pin, r1, r2, 80UL);
}

void BaseBooster::setOutputVoltmeter(uint8_t pin, float r1, float r2)
{
    output_meter = new RustyVoltmeter(pin, r1, r2, 50UL);
}

void BaseBooster::setOutputPIN(uint8_t pin)
{
    pwm_pin = pin;
    pinMode(pwm_pin, OUTPUT);
    setPWM(0);
}

void BaseBooster::setPWM(int val)
{
    analogWrite(pwm_pin, val);
}

void BaseBooster::setPID(double KP, double KI, double KD, double sample_ms, unsigned char min_pwm, unsigned char max_pwm)
{
    pid = new BoostPID(KP, KI, KD, sample_ms, min_pwm, max_pwm);
}

void BaseBooster::setOutVoltChangeHandler(void (*listener)(float))
{
    if (output_meter == nullptr)
    {
        return;
    }
    output_meter->addAvgChangeListener(listener);
}

void BaseBooster::setInputVoltChangeHandler(void (*listener)(float))
{
    if (source_meter == nullptr)
    {
        return;
    }
    source_meter->addAvgChangeListener(listener);
}

void BaseBooster::setPWMChangeHandler(void (*listener)(int))
{
    if (pid == nullptr)
    {
        return;
    }
    pid->setPwmHandler(listener);
}

String BaseBooster::floatToString(float *op_val)
{
    return output_meter->floatToString(op_val);
}

void BaseBooster::setPoint(double val)
{
    if (pid == nullptr)
    {
        return;
    }
    pid->setPoint(val);
}