#include <easy_boost.h>

EasyBoost::EasyBoost() : BaseBooster()
{
    pid = nullptr;
    source_meter = nullptr;
    output_meter = nullptr;
}

EasyBoost::~EasyBoost()
{
    if (pid != nullptr)
    {
        delete pid;
        pid = nullptr;
    }
    if (source_meter != nullptr)
    {
        delete source_meter;
        source_meter = nullptr;
    }
    if (output_meter != nullptr)
    {
        delete output_meter;
        output_meter = nullptr;
    }
}

void EasyBoost::update()
{
    if (!canIRead())
    {
        return;
    }
    pid->syncVoltage(output_meter->getAvgVoltage());
    setPWM(pid->compute());
    if (source_meter != nullptr)
    {       
        source_meter->update();        
    }
}

bool EasyBoost::canIRead()
{
    return (pid != nullptr && output_meter != nullptr);
}