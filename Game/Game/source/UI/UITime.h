#pragma once
#include "UINumber.h"
#include <memory>
#include "UI2DBase.h"
#include "UIInAndOut.h"

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

    int GetNowTime() {
        return _nowNum;
    }

    bool GetEndNow() {
        return _isEndNow;
    }

private:

    std::unique_ptr<UI2DBase> _pTimeBase;
    std::unique_ptr<UINumber> _pUINumber;
    std::unique_ptr<UIInAndOut> _pBaseInAndOut;
    std::unique_ptr<UIInAndOut> _pNumInAndOut;

    int _maxNum;

    int _startTime;
    int _startNum;
    int _nowNum;

    bool _isStart;
    bool _isStop;
    bool _isEnd;

    bool _isEndNow;  //全フレームがスタートで今エンドの時true;
};