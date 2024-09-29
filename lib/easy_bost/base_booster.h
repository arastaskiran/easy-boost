
#ifndef BASE_BOOSTER_H
#define BASE_BOOSTER_H

#include <stdint.h>
#include <Arduino.h>
#include <stdlib.h>
#include <rusty_voltmeter.h>

class BaseBooster
{
public:
BaseBooster();
~BaseBooster();

void setSourceVoltmeter(uint8_t pin, float r1, float r2);

void setOutputVoltmeter(uint8_t pin, float r1, float r2);

void setOutChangeHandler(void (*listener)(float));

void setInputChangeHandler(void (*listener)(float));

private:
    RustyVoltmeter *source_meter;
    RustyVoltmeter *output_meter;
};
#endif