
#ifndef BOOST_PID_H
#define BOOST_PID_H

#include <Arduino.h>

/**
 * @class BoostPID
 * @brief A class for implementing a PID controller for controlling the PWM signal in a boost converter.
 *
 * The BoostPID class handles the PID algorithm to regulate the output voltage of a boost converter.
 * It calculates the necessary PWM value based on the difference between the measured voltage and
 * the desired setpoint.
 */
class BoostPID
{
public:
    /**
     * @brief Construct a new BoostPID object.
     *
     * Initializes the PID controller with the provided parameters or default values.
     *
     * @param KP Proportional gain.
     * @param KI Integral gain.
     * @param KD Derivative gain.
     * @param sample_ms Sampling time in milliseconds.
     * @param min_pwm Minimum allowed PWM value.
     * @param max_pwm Maximum allowed PWM value.
     */
    BoostPID(double KP = 1.0, double KI = 0.5, double KD = 0.2, unsigned long sample_ms = 100UL, unsigned char min_pwm = 0, unsigned char max_pwm = 255);

    /**
     * @brief Destroy the BoostPID object.
     *
     * Frees up any resources used by the PID controller.
     */
    ~BoostPID();

    /**
     * @brief Compute the new PWM output based on the PID algorithm.
     *
     * This function calculates the PID output using the current voltage measurement and setpoint.
     * It returns the appropriate PWM value to be used for controlling the boost converter.
     *
     * @return int The computed PWM value (0-255).
     */
    int compute();

    /**
     * @brief Set the desired output voltage setpoint.
     *
     * @param val The target voltage for the PID controller.
     */
    void setPoint(double val);

    /**
     * @brief Update the current voltage measurement.
     *
     * This function is used to provide the measured voltage to the PID controller so it can
     * calculate the error between the setpoint and the measured value.
     *
     * @param val The current measured voltage.
     */
    void syncVoltage(float val);

    /**
     * @brief Set the handler for updating the PWM output.
     *
     * This function allows you to provide a callback function that will be called when the
     * computed PWM value needs to be applied.
     *
     * @param listener A function pointer to the PWM update handler.
     */
    void setPwmHandler(void (*listener)(int));

    /**
     * @brief Reset the PID controller state.
     *
     * Resets the integral and derivative terms and clears the last error to start fresh.
     */
    void reset();

private:
    double *kp;                 ///< Pointer to the proportional gain value.
    double *ki;                 ///< Pointer to the integral gain value.
    double *kd;                 ///< Pointer to the derivative gain value.
    double set_point;           ///< The desired setpoint for the output voltage.
    double error;               ///< The current error (difference between setpoint and measured value).
    double last_error;          ///< The error from the previous sample.
    double integral;            ///< Accumulated integral term.
    double derivative;          ///< Derivative term based on the change in error.
    int output;                 ///< The computed PWM output value.
    double measured_value;      ///< The current measured voltage.
    unsigned long last_time;    ///< The last time the PID computation was performed.
    unsigned long sample_time;  ///< The time interval between PID computations.
    unsigned long current_time; ///< The current time used for computing sample intervals.
    unsigned char min_p;        ///< Minimum allowed PWM value.
    unsigned char max_p;        ///< Maximum allowed PWM value.

    /**
     * @brief Check if it is time to sample the PID controller.
     *
     * @return true If it is time to sample.
     * @return false Otherwise.
     */
    bool canISample();

    /**
     * @brief Function pointer to the handler for applying the PWM output.
     *
     * This function is called when the computed PWM value is ready to be applied to the output.
     *
     * @param pwmListener Function pointer for the PWM output handler.
     */
    void (*pwmListener)(int);
};

#endif