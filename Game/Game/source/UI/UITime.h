#pragma once
#include "UINumber.h"
#include <memory>
#include "UI2DBase.h"

class UITime {
public:
    UITime();
    virtual ~UITime();

    bool Init(int maxNum ,int digit);
    void Process();
    void Draw();

    void SetStart(int startNum);
    void SetStop(bool stop) {
        _isStop = stop;
    }

private:

   // bool SetNumber(int num);

    std::unique_ptr<UI2DBase> _pTimeBase;
    std::unique_ptr<UINumber> _pUINumber;

    int _maxNum;

    int _startTime;
    int _startNum;
    int _nowNum;

    bool _isStart;
    bool _isStop;
    bool _isEnd;
};