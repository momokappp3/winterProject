#pragma once
#include "UI2DBase.h"
#include "UI2DSelectBase.h"
#include <memory>
#include "../../../../AppFrame/Types.h"

class UIPopUp {
public:
    UIPopUp();
    virtual ~UIPopUp();

    bool Init();
    void Process();
    void Draw();

    int GetOk() {
        return _ok;
    }

    int GetClose() {
        return _close;
    }

    bool GetNowMode() {
        return _nowMode;
    }

    void SetNowMode(bool nowMode) {
        _nowMode = nowMode;
    }

    void SetMouse(int x, int y) {
        _mouse.x = x;
        _mouse.y = y;
    }

    void SetTrgLeft(int left) {
        _trgLeft = left;
    }

    bool GetTrgLeft() {
        return _trgLeft;
    }

    void SetPopString(PopString string) {
        _popString = string;
    }

private:
    std::unique_ptr<UI2DBase> _pPopUpBase;
    std::unique_ptr<UI2DSelectBase> _pOkBSelectBase;
    std::unique_ptr<UI2DSelectBase> _pCloselBBase;

    int _ok;
    int _close;

    Point _mouse;
    bool _trgLeft;

    bool _nowMode;

    PopString _popString;

};