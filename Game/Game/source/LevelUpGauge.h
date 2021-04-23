#pragma once
#include "UI/UIGauge.h"

class LevelUpGauge :public UIGauge{
public:
    LevelUpGauge();
    virtual ~LevelUpGauge();

    //Base�N���X��Init�̌ĂіY�ꂪ�����悤�ɋC��t����
    void Process()override;
    bool SetRate(int rate)override;

    void SetLoopNum(int loop) {
        _loopNum = loop;
    }

private:

    int _loopNum;
    bool _isLoop;
};

