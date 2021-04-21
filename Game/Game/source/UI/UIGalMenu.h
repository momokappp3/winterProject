#pragma once
#include <memory>
#include "UI2DBase.h"
#include "UI2DSelectBase.h"
#include "UIInAndOut.h" 
#include "../../../../AppFrame/Tween.h"
#include "UIGauge.h"
#include "UINumber.h"

class UIGalMenu{
public:
    UIGalMenu();
    virtual ~UIGalMenu();

    bool Init(std::shared_ptr<SoundManager>& soundManager);
    void Process();
    void Draw();

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

    int GetSelectCancel() {
        return _cancel;
    }

    int GetSelectSetting() {
        return _setting;
    }

    void SetSelectSetting(bool num) {
        _setting = num;
    }

    int GetSelectStory() {
        return _story;
    }

    int GetSelectItem() {
        return _item;
    }

    void SetSelectItem(int num) {
        _item = num;
    }

    void SetMolecule(int molecule) {
        _molecule = molecule;
    }

    void SetCoin(int coin) {
        _coin = coin;
    }

    void SetFavor(int favor) {
        _favor = favor;
    }

private:

    bool DrawInit();
    void MoveInit();
    void MoveProcess();

    //描画
    std::unique_ptr <UI2DSelectBase> _pSettingSelectBase;
    std::unique_ptr<UI2DSelectBase> _pCancelSelectBase;
    std::unique_ptr<UI2DSelectBase> _pBstorySelectBase;
    std::unique_ptr<UI2DSelectBase> _pBitemSelectBase;

    std::unique_ptr<UIGauge> _pBarPinkBase;
    std::unique_ptr<UIGauge> _pBarRedBase;

    std::unique_ptr<UI2DBase> _pCircleBase;

    std::unique_ptr<UI2DBase> _pCoinBaseBase;
    std::unique_ptr<UINumber> _pCoinNum;

    std::unique_ptr<UINumber> _pTrustNum;

    //アニメーション出し入れ
    std::unique_ptr<UIInAndOut> _pSettingInAndOut;
    std::unique_ptr<UIInAndOut> _pCancelInAndOut;
    std::unique_ptr<UIInAndOut> _pBstoryInAndOut;
    std::unique_ptr<UIInAndOut> _pBitemInAndOut;

    std::unique_ptr<UIInAndOut> _pBarPinkInAndOut;
    std::unique_ptr<UIInAndOut> _pBarRedInAndOut;

    std::unique_ptr<UIInAndOut> _pCircleInAndOut;

    std::unique_ptr<UIInAndOut> _pCoinBaseInAndOut;
    std::unique_ptr<UIInAndOut> _pCoinNumInAndOut;
    std::unique_ptr<UIInAndOut> _pTrustNumInAndOut;

    std::shared_ptr<SoundManager> _pSoundManager;

    bool _start;
    bool _end;

    int _cancel;
    int _setting;
    int _story;
    int _item;

    int _mouseX;
    int _mouseY;

    int _molecule;
    int _coin;
    int _favor;

    int _lastMolecule;

};