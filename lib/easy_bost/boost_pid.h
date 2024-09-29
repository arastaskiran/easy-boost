
#ifndef BOOST_PID_H
#define BOOST_PID_H

#include <Arduino.h>

class BoostPID
{
public:
    BoostPID(double KP = 1.0, double KI = 0.5, double KD = 0.2, double sample_ms = 100, unsigned char min_pwm = 0, unsigned char max_pwm = 255);
    ~BoostPID();

    void compute();
    void setPoint(double val);
    void setInput(float val);

private:
    double kp;
    double ki;
    double kd;
    double set_point;
    double error;
    double last_error;
    double integral;
    double derivative;
    double output;
    double measured_value;
    unsigned long last_time;
    unsigned long sample_time;
    unsigned long current_time;
    unsigned char min_p;
    unsigned char max_p;
    bool canISample();
};

#endif