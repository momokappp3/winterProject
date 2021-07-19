#pragma once
#include "UIUseBase.h"
#include "UI2DBase.h"
#include "UI2DSelectBase.h"
#include "../../../../AppFrame/Tween.h"

class UIRoomSetting :public UIUseBase{
public:
    UIRoomSetting();
    virtual ~UIRoomSetting();

    //オーバーライド
    bool Init(std::shared_ptr<SoundManager>& soundManager);
    void Process() override;
    void Draw() override;

private:

    std::unique_ptr<Tween> _pTween;

    std::unique_ptr<UI2DBase> _pBackImageBase;
    std::unique_ptr<UI2DSelectBase> _pOutBSelectBase;
    std::unique_ptr<UI2DSelectBase> _pTitleBSelectBase;

    std::shared_ptr<SoundManager> _pSoundManager;

    //背景の出現処理  基底の_startがtrueだったら
    //ここではDrawAreaを使う

    /*
    基底クラスのコマンドベクターに二つ入れる上からボタンが選択されたか
    */
};