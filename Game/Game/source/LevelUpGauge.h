#pragma once
#include "UI/UIGauge.h"

class LevelUpGauge :public UIGauge{
public:
    LevelUpGauge();
    virtual ~LevelUpGauge();

    //BaseクラスのInitの呼び忘れが無いように気を付ける
    void Process()override;
    bool SetRate(int rate)override;

    void SetLoopNum(int loop) {
        _loopNum = loop;
    }

private:

    int _loopNum;
    bool _isLoop;
};

