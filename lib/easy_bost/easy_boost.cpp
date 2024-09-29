#include <easy_boost.h>

void EasyBoost::update()
{
    if (!canIRead())
    {
        return;
    }
    pid->syncVoltage(output_meter->getAvgVoltage());
    setPWM(pid->compute());
}

bool EasyBoost::canIRead()
{
    return (pid != nullptr && output_meter != nullptr);
}