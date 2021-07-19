/*****************************************************************//**
 * \file   RoomGameUI.h
 * \brief  UIのやりとりアイテム使用
 * \author momoka
 * \date   2021 7/9
 *********************************************************************/
#pragma once
#include "RoomGameUI.h"
#include "UIRoomMenuInit.h"
#include <memory>
#include ".././.../../../../../AppFrame/Types.h"
#include "../../../../AppFrame/MouseInput.h"
#include "UIRoomMenu.h"
#include "UIRoomSetting.h"
#include "UIRoomItem.h"
#include "UIRoomStory.h"
#include "UITime.h"
#include "../Novel/scripts/script_engine.h"

class RoomGameUI {
public:
    RoomGameUI();
    virtual ~RoomGameUI();

    bool Init(std::shared_ptr<SoundManager>& soundManager, std::shared_ptr<PlayerInfo>& playerInfo);
    void Process();
    void Draw();
    void Terminate();

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

    RoomGameUIType _type;  //現在表示しているタイプ
    FaceInfo _faceInfo;

    std::unique_ptr<UIRoomMenuInit> _pUIRoomMenuInit;
    std::unique_ptr<UIRoomMenu> _pUIRoomMenu;
    std::unique_ptr<UIRoomSetting> _pUIRoomSetting;
    std::unique_ptr<UIRoomItem> _pUIRoomItem;
    std::unique_ptr<UIRoomStory> _pUIRoomStory;
    std::shared_ptr<SoundManager> _pSoundManager;

    std::unique_ptr<UIPopUp> _pUIPopUp;
    std::unique_ptr<UITime> _pDrunkTime;
    std::unique_ptr<amg::ScriptEngine> _pScriptEngin;
    std::unique_ptr<MouseInput> _pMouseInput;

    //このクラスに表示する画像
    std::unique_ptr<UI2DSelectBase> _pCloselBScript;
    std::unique_ptr<UI2DSelectBase> _pUpButton;
    std::unique_ptr<UI2DSelectBase> _pDownButton;

    std::shared_ptr<PlayerInfo> _pPlayerInfo;

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