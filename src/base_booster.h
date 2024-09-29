
#ifndef BASE_BOOSTER_H
#define BASE_BOOSTER_H

#include <stdint.h>
#include <Arduino.h>
#include <stdlib.h>
#include <rusty_voltmeter.h>
#include <boost_pid.h>

/**
 * @class BaseBooster
 * @brief A class to control a boost converter using a PID controller and voltage meters.
 *
 * The BaseBooster class is responsible for controlling the output voltage of a boost converter
 * by using a PID control loop. It integrates two voltmeters for input and output voltage
 * monitoring, and provides handlers for various events such as voltage or PWM changes.
 */
class BaseBooster
{
public:
    /**
     * @brief Construct a new BaseBooster object.
     *
     * Initializes the BaseBooster instance with default settings.
     */
    BaseBooster();

    /**
     * @brief Set the input voltmeter to monitor source voltage.
     *
     * @param pin The analog pin to which the source voltmeter is connected.
     * @param r1 The resistance value of the first resistor in the voltage divider.
     * @param r2 The resistance value of the second resistor in the voltage divider.
     */
    void setSourceVoltmeter(uint8_t pin, float r1, float r2);

    /**
     * @brief Set the output voltmeter to monitor the boosted output voltage.
     *
     * @param pin The analog pin to which the output voltmeter is connected.
     * @param r1 The resistance value of the first resistor in the voltage divider.
     * @param r2 The resistance value of the second resistor in the voltage divider.
     */
    void setOutputVoltmeter(uint8_t pin, float r1, float r2);

    /**
     * @brief Set a listener for changes in the output voltage.
     *
     * This function allows you to provide a callback function that will be called
     * when the output voltage changes.
     *
     * @param listener A function pointer to the voltage change handler.
     */
    void setOutVoltChangeHandler(void (*listener)(float));

    /**
     * @brief Set a listener for changes in the input voltage.
     *
     * This function allows you to provide a callback function that will be called
     * when the input voltage changes.
     *
     * @param listener A function pointer to the input voltage change handler.
     */
    void setInputVoltChangeHandler(void (*listener)(float));

    /**
     * @brief Set a listener for changes in the PWM value.
     *
     * This function allows you to provide a callback function that will be called
     * when the PWM signal changes.
     *
     * @param listener A function pointer to the PWM change handler.
     */
    void setPWMChangeHandler(void (*listener)(int));

    /**
     * @brief Set the PWM output pin.
     *
     * @param pin The pin where the PWM signal is output to control the boost converter.
     */
    void setOutputPIN(uint8_t pin);

    /**
     * @brief Set the PID parameters for controlling the boost converter.
     *
     * @param KP Proportional gain.
     * @param KI Integral gain.
     * @param KD Derivative gain.
     * @param sample_ms Sampling time in milliseconds.
     * @param min_pwm Minimum allowed PWM value.
     * @param max_pwm Maximum allowed PWM value.
     */
    void setPID(double KP = 1.0, double KI = 0.5, double KD = 0.2, double sample_ms = 100, unsigned char min_pwm = 0, unsigned char max_pwm = 255);

    /**
     * @brief Convert a float value to a string.
     *
     * @param op_val Pointer to the float value to convert.
     * @return String The converted string representation of the float value.
     */
    String floatToString(float *op_val);

    /**
     * @brief Set the desired output voltage setpoint for the PID controller.
     *
     * @param val The target voltage value for the boost converter.
     */
    void setPoint(double val);

protected:
    RustyVoltmeter *source_meter; ///< Pointer to the source (input) voltmeter.
    RustyVoltmeter *output_meter; ///< Pointer to the output voltmeter.
    BoostPID *pid;                ///< Pointer to the PID controller.

    /**
     * @brief Set the PWM value for the boost converter.
     *
     * This function directly controls the PWM output based on the PID output.
     *
     * @param val The PWM value to set (0-255).
     */
    void setPWM(int val);

private:
    uint8_t pwm_pin; ///< The pin used for PWM output to control the boost converter.
};
#endif