#pragma once
#include "UI2DBase.h"
#include <memory>
#include "../../../../AppFrame/Types.h"
#include "UI2DSelectBase.h"
#include "UIInAndOut.h"
#include "UIGauge.h"
#include "../../../../AppFrame/Input.h"
#include "../SoundManager.h"

class UIRoomMenuInit {
public:
    UIRoomMenuInit();
    virtual ~UIRoomMenuInit();

    bool Init(std::shared_ptr<SoundManager>& soundManager);
    void Process();
    void Draw();

    RoomGameUIType GetType() {
        return _ModeType;
    }

    int GetSelect() {
        return _select;
    }
    void SetSelect(int num) {
        _select = num;
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

    RoomGameUIType _ModeType;

    std::unique_ptr<UI2DSelectBase> _pMenuSelectBase;
    std::unique_ptr<UIInAndOut> _pMenuInAndOut;
    std::shared_ptr<SoundManager> _pSoundManager;

    bool _start;
    bool _end;

    int _num;

    int _select;  //選択されていたら1

    int _mouseX;
    int _mouseY;

};
