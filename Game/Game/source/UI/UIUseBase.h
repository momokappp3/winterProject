#pragma once
#include "UI2DSelectBase.h"
#include <memory>
#include <vector>

class UIUseBase {
public:
    UIUseBase();
    virtual ~UIUseBase();

    virtual bool Init();
    virtual void Process();
    virtual void Draw();

    void SetMousePoint(int x, int y) {  //使用クラスで受け取る
        _mouseX = x;
        _mouseY = y;
    }

    void SetMouseLeft(bool left) {
        _mouseLeft = left;
    }

    void SetNowMode(bool nowMode) {
        _nowMode = nowMode;
    }

    void SetStart(bool start) {
        _start = start;
    }

    void SetEnd(bool end) {
        _end = end;
    }

    bool GetComandSelect(int index) {
        return _vComandSelect[index];
    }

    int GetClose() {
        return _closeB;
    }

protected:

    std::vector<bool> _vComandSelect;

    Point _closePoint;

    int _mouseX;
    int _mouseY;
    bool _mouseLeft;

    bool _nowMode;
    bool _closeUse;

private:

    //void MoveBackImage(); //3つ使う予定

    std::unique_ptr<UI2DSelectBase> _pCloselBBase;

    bool _start;  //このモードが開始した
    bool _end;   //このモードが閉じた
    bool _myClose;

    int _closeB;

};