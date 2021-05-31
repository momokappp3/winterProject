#pragma once
#include "GalGameUI.h"
#include "UIGalMenuInit.h"
#include <memory>
#include ".././.../../../../../AppFrame/Types.h"
#include "../../../../AppFrame/MouseInput.h"
#include "UIGalMenu.h"
#include "UIGalSetting.h"
#include "UIGalItem.h"
#include "UIGalStory.h"
#include "UITime.h"
#include "../Novel/scripts/script_engine.h"

/*
UIのやり取り
アイテム使用
*/

class GalGameUI {
public:
    GalGameUI();
    virtual ~GalGameUI();

    bool Init(std::shared_ptr<SoundManager>& soundManager);
    void Process();
    void Draw();
    void Terminate();

    void SetMolecule(int molecule) {
        _molecule = molecule;
    }

    void SetFavor(int favor) {  //参照渡しに変更
        _favor = favor;
    }
    //====================================
    //boolSetGet

    bool GetSakeItem() {
        return _sakeItem;
    }

    bool GetGoTitle() {
        return _goTitle;
    }

    void SetGoTitle(bool title) {
        _goTitle = title;
    }

    bool GetGoActoin() {
        return _goAction;
    }

    void SetGoAction(bool action) {
        _goAction = action;
    }

    bool GetKaneOK() {
        return _kaneOK;
    }
    void SetKaneOK(bool ok) {
        _kaneOK = ok;
    }

    bool GetKaneNO() {
        return _kaneNo;
    }
    void SetKaneNo(bool no) {
        _kaneNo = no;
    }

    FaceInfo GetFaceInfo() {
        _isFaceInfo = false;
        return _faceInfo;
    }

    bool GetIsFaceInfo() {
        return _isFaceInfo;
    }
private:

    void SettingProcess();
    void ItemProcess();
    void StoryProcess();

    GalGameUIType _type;  //現在表示しているタイプ
    FaceInfo _faceInfo;

    std::unique_ptr<UIGalMenuInit> _pUIGalMenuInit;
    std::unique_ptr<UIGalMenu> _pUIGalMenu;
    std::unique_ptr<UIGalSetting> _pUIGalSetting;
    std::unique_ptr<UIGalItem> _pUIGalItem;
    std::unique_ptr<UIGalStory> _pUIGalStory;
    std::shared_ptr<SoundManager> _pSoundManager;

    std::unique_ptr<UIPopUp> _pUIPopUp;
    std::unique_ptr<UITime> _pDrunkTime;
    std::unique_ptr<amg::ScriptEngine> _pScriptEngin;
    std::unique_ptr<MouseInput> _pMouseInput;

    //このクラスに表示する画像
    std::unique_ptr<UI2DSelectBase> _pCloselBScript;
    std::unique_ptr<UI2DSelectBase> _pUpButton;
    std::unique_ptr<UI2DSelectBase> _pDownButton;

    int _molecule;  //barの値
    int _favor;  //数字に渡す値
    int _coin;
    int _mentalNum;  //赤いバーの値

    int _basicFavor;
    int _giveCoin;

    bool _sakeItem;
    bool _kaneOK;
    bool _kaneNo;
    bool _goTitle;
    bool _goAction;

    bool _scriptClose;
    bool _upB;
    bool _downB;

    bool _okFlag;

    bool _isFaceInfo;
};
