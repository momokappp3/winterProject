#pragma once
#include "UI2DBase.h"
#include <memory>
#include "../../../../AppFrame/Types.h"
#include "UI2DSelectBase.h"
#include "UIInAndOut.h"
#include "UIGauge.h"
#include "../../../../AppFrame/Input.h"

class UIGalMenuInit {
public:
    UIGalMenuInit();
    virtual ~UIGalMenuInit();

    bool Init();
    void Process();
    void Draw();

    GalGameUIType GetType() {
        return _ModeType;
    }

    int GetSelect() {
        return _select;
    }

    void SetStart(bool start) {
        _start = start;
    }

    void SetEnd(bool end) {
        _end = end;
    }

    void SetMousePoint(int x, int y) {  //使用クラスで受け取る
        _mouseX = x;
        _mouseY = y;
    }

private:

    GalGameUIType _ModeType;

    std::unique_ptr<UI2DSelectBase> _pMenuSelectBase;
    std::unique_ptr<UIInAndOut> _pMenuInAndOut;

    bool _start;
    bool _end;

    int _num;

    int _select;  //選択されていたら1

    int _mouseX;
    int _mouseY;

};
