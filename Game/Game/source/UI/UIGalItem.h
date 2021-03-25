#pragma once
#include "UIUseBase.h"
#include "UI2DBase.h"
#include "UI2DSelectBase.h"
#include "../../../../AppFrame/Tween.h"
#include <String>
#include "UIPopUp.h"

class UIGalItem:public UIUseBase {
public:
    UIGalItem();
    virtual ~UIGalItem();

    bool Init() override;
    void Process() override;
    void Draw() override;

private:

    //std::unique_ptr<Tween> _pTween;

    std::unique_ptr<UI2DBase> _pBackImageBase;
    std::unique_ptr<UI2DSelectBase> _pMoneyBSelectBase;
    std::unique_ptr<UI2DSelectBase> _pTequilaBSelectBase;

    std::unique_ptr<UIPopUp> _pUIPopUp;

    /*
    基底クラスのコマンドベクターに二つ入れる上からボタンが選択されたか
    */

    std::vector<std::string> _vString;

};