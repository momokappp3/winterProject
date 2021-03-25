#pragma once

#include "../../AppFrame/Tween.h"
#include <memory>
#include "../../AppFrame/Types.h"

/*
UI�̏o������̓���
*/

class UIInAndOut {
public:
    UIInAndOut();
    virtual ~UIInAndOut();

    bool Init();
    void Process();

    //��ʊO������ɂ��铮������
    void SetStartPosition(Point start) {  //Init�ŕK���w��@
        _start = start;
    }

    void SetEndPosition(Point end) {  //Init�ŕK���w��
        _end = end;
    }

    void SetNowPosition(Point now) {  //Init�ōŏ��ɒu���Ă����ʒu��K���w��
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

    Point _start;  //�摜�̏����ʒu
    Point _end;  //�\���������ꏊ
    Point _now;

};