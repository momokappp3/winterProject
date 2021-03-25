#pragma once

#include "../../AppFrame/Tween.h"
#include <memory>
#include "../../AppFrame/Types.h"

/*
UIの出し入れの動き
*/

class UIInAndOut {
public:
    UIInAndOut();
    virtual ~UIInAndOut();

    bool Init();
    void Process();

    //画面外から内にする動き許可
    void SetStartPosition(Point start) {  //Initで必ず指定　
        _start = start;
    }

    void SetEndPosition(Point end) {  //Initで必ず指定
        _end = end;
    }

    void SetNowPosition(Point now) {  //Initで最初に置いておく位置を必ず指定
        _now = now;
    }

    void SetIsStart(bool flag) {
        _isStart = flag;
    }

    void SetIsEnd(bool flag) {
        _isEnd = flag;
    }

    Point GetNowPosition() {
        return _now;
    }

private:

    bool _isStart;
    bool _isEnd;

    std::unique_ptr<Tween> _pTween;

    Point _start;  //画像の初期位置
    Point _end;  //表示したい場所
    Point _now;

};