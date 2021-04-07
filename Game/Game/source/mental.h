#pragma once
#include <memory>
#include "../../../AppFrame/Tween.h"
#include "UI/UIGauge.h"

class Mental {
public:
    Mental();
    virtual ~Mental();

    bool Init();
    void Process();
    void Draw();

    void SetMental(int mental) {
        _mental = mental;
    }

    void SetBarPoint(Point point) {  //menuで動いたポインタをセットさせる
        _pBarRedBase->SetPoint(0,point);
        _pBarRedBase->SetPoint(1, point);
    }

    DrawInfo GetInAndInfo() {  //Initの後に呼び出す
        DrawInfo info;
        _pBarRedBase->GetDrawInfo(0, info);
        return info;
    }

private:
    std::unique_ptr<Tween> _pMentalTween;
    std::unique_ptr<UIGauge> _pBarRedBase;

    int _mental;
    int _minMental;
    int _maxMental;
};