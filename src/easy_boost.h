
#ifndef EASY_BOOST_H
#define EASY_BOOST_H

#include <base_booster.h>

/**
 * @class EasyBoost
 * @brief A simplified class for managing a boost converter using the BaseBooster as the base class.
 *
 * The EasyBoost class inherits from the BaseBooster and provides additional functionality to
 * easily manage and update the boost converter operation. It introduces an update loop and
 * a method to determine when voltage readings can be taken.
 */
class EasyBoost : public BaseBooster
{
public:
    /**
     * @brief Construct a new EasyBoost object.
     *
     * Initializes the EasyBoost instance with default settings and prepares the boost converter
     * for operation.
     */
    EasyBoost();

    /**
     * @brief Destroy the EasyBoost object.
     *
     * Cleans up any resources used by the EasyBoost instance.
     */
    ~EasyBoost();

    /**
     * @brief Update the boost converter operation.
     *
     * This function should be called regularly (e.g., in the main loop) to update the boost
     * converter's state and apply any necessary changes to the PID or PWM output.
     */
    void update();

    /**
     * @brief Check if it's time to read the voltage values.
     *
     * This function determines if the voltage values can be read based on internal timing logic.
     * It ensures that readings are taken at appropriate intervals.
     *
     * @return true If voltage readings can be taken.
     * @return false Otherwise.
     */
    bool canIRead();
};
#endif