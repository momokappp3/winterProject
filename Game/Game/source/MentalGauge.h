#pragma once
#include <memory>
#include "../../../AppFrame/Tween.h"
#include "UI/UIGauge.h"

class MentalGauge : public UIGauge{
public:
    MentalGauge();
    virtual ~MentalGauge();

    void Process()override;

    bool SetRate(int num)override;

private:

    int _mental;
    int _minMental;
    int _maxMental;

    bool _maxStart;
};