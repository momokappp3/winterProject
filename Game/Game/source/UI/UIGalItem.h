#pragma once
#include "UIUseBase.h"
#include "UI2DBase.h"
#include "UI2DSelectBase.h"
#include "../../../../AppFrame/Tween.h"
#include "UIPopUp.h"
#include "../../../../AppFrame/Types.h"

class UIGalItem:public UIUseBase {
public:
    UIGalItem();
    virtual ~UIGalItem();

    bool Init() override;
    void Process() override;
    void Draw() override;

    void SetMoneyStringDraw(bool isDraw) {
        _moneyString.isDraw = isDraw;
    }

    void SetTequilaStringDraw(bool isDraw) {
        _tequilaString.isDraw = isDraw;
    }

    bool GetMoneyStringDraw() {
        return _moneyString.isDraw;
    }

    bool GetTequilaStringDraw() {
        return _tequilaString.isDraw;
    }

    PopString GetMoneyString() {
        return _moneyString;
    }

    PopString GetTequilaString() {
        return _tequilaString;
    }

    void StringAllFalse() {
        _moneyString.isDraw = false;
        _tequilaString.isDraw = false;
    }

private:

    //std::unique_ptr<Tween> _pTween;

    std::unique_ptr<UI2DBase> _pBackImageBase;
    std::unique_ptr<UI2DSelectBase> _pMoneyBSelectBase;
    std::unique_ptr<UI2DSelectBase> _pTequilaBSelectBase;

    PopString _moneyString;
    PopString _tequilaString;

};