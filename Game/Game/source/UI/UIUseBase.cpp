#include "UIUseBase.h"
#include "../../ResourceServer.h"
#include "../../Utility.h"

UIUseBase::UIUseBase() {

    _pCloselBBase = nullptr;

    _vComandSelect.clear();

    _closePoint = { 0,0 };

    _mouseX = -1;
    _mouseY = -1;
    _mouseLeft = false;

    _start = false;
    _end = false;
    _myClose = false;

    _closeB = -1;

    _nowMode = false;
    _closeUse = true;

}

UIUseBase::~UIUseBase() {
}

bool UIUseBase::Init() {

    _pCloselBBase.reset(new UI2DSelectBase);

    int handle = ResourceServer::LoadGraph("png/galUI/closeButton.png");
    int handle2 = ResourceServer::LoadGraph("png/galUI/closeButton_select.png");

    if (handle == -1 && handle2 == -1) {
        return false;
    }

    DrawInfo info = { handle,_closePoint.x,_closePoint.y,true };
    DrawInfo info2 = { handle2,_closePoint.x,_closePoint.y,true };

    _pCloselBBase->SetDrawInfo(info);
    _pCloselBBase->SetDrawInfo(info2);

    _pCloselBBase->SetRadius(20.0f);

}

void UIUseBase::Process() {

    if (_start == true) {
        _nowMode = true;
    }

    if (_end == true) {
        _nowMode = false;
    }

    _start = false;
    _end = false;

    if (_closeUse) {
        _closeB = _pCloselBBase->GetSelect();
        _pCloselBBase->SetSelect(Utility::ImageHitDetection(_mouseX, _mouseY, _pCloselBBase.get()));
    }
    _pCloselBBase->Process();

}

void UIUseBase::Draw() {
  
    _pCloselBBase->Draw();
}
