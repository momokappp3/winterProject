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

    //オーバーライド取った
    bool Init(std::shared_ptr<SoundManager>& soundManager);
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

    int GetNowItemType() {
        return _itemType;
    }
    void SetNowItemType(int type) {
        _itemType = type;
    }

    void StringAllFalse() {
        _moneyString.isDraw = false;
        _tequilaString.isDraw = false;
    }

    void SetGiveCoin(int coin);

    int GetGiveCoin() {
        return _giveCoin;
    }

private:

    std::unique_ptr<UI2DBase> _pBackImageBase;
    std::unique_ptr<UI2DSelectBase> _pMoneyBSelectBase;
    std::unique_ptr<UI2DSelectBase> _pTequilaBSelectBase;
    std::shared_ptr<SoundManager> _pSoundManager;

    PopString _moneyString;
    PopString _tequilaString;

    std::string _coinString;


    //0 =金 1= 酒
    int _itemType;

    int _giveCoin;

};