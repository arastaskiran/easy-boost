
#ifndef BASE_BOOSTER_H
#define BASE_BOOSTER_H

#include <stdint.h>
#include <Arduino.h>
#include <stdlib.h>
#include <rusty_voltmeter.h>
#include <boost_pid.h>

class BaseBooster
{
public:
    BaseBooster();
    ~BaseBooster();

    void setSourceVoltmeter(uint8_t pin, float r1, float r2);

    void setOutputVoltmeter(uint8_t pin, float r1, float r2);

    void setOutVoltChangeHandler(void (*listener)(float));

    void setInputVoltChangeHandler(void (*listener)(float));

    void setPWMChangeHandler(void (*listener)(int));

    void setOutputPIN(uint8_t pin);

    void setPID(double KP = 1.0, double KI = 0.5, double KD = 0.2, double sample_ms = 100, unsigned char min_pwm = 0, unsigned char max_pwm = 255);

    String floatToString(float *op_val);

protected:
    RustyVoltmeter *source_meter;
    RustyVoltmeter *output_meter;
    BoostPID *pid;
    void setPWM(int val);

private:
    uint8_t pwm_pin;
};
#endif