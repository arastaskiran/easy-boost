
#ifndef EASY_BOOST_H
#define EASY_BOOST_H

#include <base_booster.h>

class EasyBoost : public BaseBooster
{
public:
    void update();
    bool canIRead();
};
#endif