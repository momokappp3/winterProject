#include "GalGameUI.h"
#include "../ApplicationMain.h"
#include "../Mode/ModeTitle.h"
#include "../Mode/GalGame.h"
#include "../../Utility.h"

#define PI 3.1415926535897932384626433832795f
#define DRUNK_TIME 80

GalGameUI::GalGameUI() {

    _type = GalGameUIType::Max;

    _pUIGalMenuInit = nullptr;
    _pUIGalMenu = nullptr;
    _pUIGalSetting = nullptr;
    _pUIGalItem = nullptr;
    _pUIGalStory = nullptr;
    _pSoundManager = nullptr;

    _pUIPopUp = nullptr;
    _pDrunkTime = nullptr;
    _pScriptEngin = nullptr;
    _pMouseInput = nullptr;

    _pCloselBScript = nullptr;
    _pUpButton = nullptr;
    _pDownButton = nullptr;

    _sakeItem = false;
    _title = false;

    _scriptClose = false;
    _upB = false;
    _downB = false;

    _okFlag = false;

    _giveCoin = 0;
}

GalGameUI::~GalGameUI() {
}

bool GalGameUI::Init(std::shared_ptr<SoundManager>& soundManager) {

    if (soundManager != nullptr) {
        bool seTitle = soundManager->LoadSECommon();

        if (!seTitle) {
            return false;
        }
    }
    else {
        return false;
    }

    _pSoundManager = soundManager;

    _type = GalGameUIType::MenuIinit;

    _pUIGalMenuInit.reset(new UIGalMenuInit);
    _pUIGalMenu.reset(new UIGalMenu);
    _pUIGalSetting.reset(new UIGalSetting);
    _pUIGalItem.reset(new UIGalItem);
    _pUIGalStory.reset(new UIGalStory);

    _pUIPopUp.reset(new UIPopUp);
    _pDrunkTime.reset(new UITime);
    _pScriptEngin.reset(new amg::ScriptEngine);
    _pMouseInput.reset(new MouseInput);

    _pCloselBScript.reset(new UI2DSelectBase);
    _pUpButton.reset(new UI2DSelectBase);
    _pDownButton.reset(new UI2DSelectBase);

    if (!_pUIGalMenu->Init() || !_pUIGalMenuInit->Init() || !_pUIGalItem->Init() ||!_pUIGalSetting->Init() || 
        !_pUIGalStory->Init() || !_pUIPopUp->Init()) {
        return false;
    }

    //xボタン
    int handle = ResourceServer::LoadGraph("png/galUI/closeButton.png");
    int handle2 = ResourceServer::LoadGraph("png/galUI/closeButton_select.png");

    if (handle == -1 && handle2 == -1) {
        return false;
    }

    DrawInfo info = { handle,412,270,true };
    DrawInfo info2 = { handle2,412,270,true };

    _pCloselBScript->SetDrawInfo(info);
    _pCloselBScript->SetDrawInfo(info2);
    _pCloselBScript->SetRadius(20);

    //上矢印
    handle = ResourceServer::LoadGraph("png/galUI/use/arrowUp.png");
    handle2 = ResourceServer::LoadGraph("png/galUI/use/arrowUpSelect.png");

    if (handle == -1 && handle2 == -1) {
        return false;
    }

    info = { handle,1700,400,false};
    info2 = { handle2,1700,400,false };

    _pUpButton->SetDrawInfo(info);
    _pUpButton->SetDrawInfo(info2);
    _pUpButton->SetRect();

    //下矢印
    handle = ResourceServer::LoadGraph("png/galUI/use/arrowDown.png");
    handle2 = ResourceServer::LoadGraph("png/galUI/use/arrowDownSelect.png");

    if (handle == -1 && handle2 == -1) {
        return false;
    }

    info = { handle,1700,515,false };
    info2 = { handle2,1700,515,false };

    _pDownButton->SetDrawInfo(info);
    _pDownButton->SetDrawInfo(info2);
    _pDownButton->SetRect();


    if (!_pScriptEngin->Initialize("source/excel/test.json")) {
        return false;
    }

    if (!_pDrunkTime->Init(99, 2)) {
        return false;
    }

    _pScriptEngin->SetState(amg::ScriptEngine::ScriptState::END);

    _giveCoin = 2500;
    _coin = 5000;

    auto onSelect = []() {
        //サウンド鳴らす
        //_pSoundManager->

    };

    _pDownButton->SetOnSelect(onSelect);

    return true;
}

void GalGameUI::Process() {

    _pMouseInput->Process();
    _pUIPopUp->Process();

    if (_pScriptEngin->IsFavor()) {

        int getNowFavor = 0;
        
        getNowFavor = _pScriptEngin->GetFavor();  //分子9900まで

        _favor += getNowFavor / 100;
        _molecule = getNowFavor % 100;
    }
    
    if (_molecule >= 9900) {
        _molecule = 9900;
    }

    _pUIGalMenu->SetFavor(_favor);
    _pUIGalMenu->SetMolecule(_molecule);

    if (_type == GalGameUIType::Setting) {
        SettingProcess();
    }

    if (_type == GalGameUIType::Item) {
        ItemProcess();
    }

    if (_type == GalGameUIType::Story) {
        StoryProcess();
    }


    if (_type == GalGameUIType::MenuIinit) {
        _pUIGalMenuInit->SetMousePoint(_pMouseInput->GetXNum(), _pMouseInput->GetYNum());
    }

    if (_type == GalGameUIType::Menu && _type!=GalGameUIType::Item && _type != GalGameUIType::Story && 
        _type != GalGameUIType::Item && _pScriptEngin->GetState() == amg::ScriptEngine::ScriptState::END) {
        _pUIGalMenu->SetMousePoint(_pMouseInput->GetXNum(), _pMouseInput->GetYNum());
    }

    if (_type == GalGameUIType::Setting && _type != GalGameUIType::Item && _type != GalGameUIType::Story &&
        _pMouseInput->GetYNum() && _pScriptEngin->GetState() == amg::ScriptEngine::ScriptState::END) {
        _pUIGalSetting->SetMousePoint(_pMouseInput->GetXNum(), _pMouseInput->GetYNum());
    }

    if (_type == GalGameUIType::Item && _type != GalGameUIType::Story && _pScriptEngin->GetState() == amg::ScriptEngine::ScriptState::END) {
        _pUIGalItem->SetMousePoint(_pMouseInput->GetXNum(), _pMouseInput->GetYNum());
        _pUIGalItem->SetMouseLeft(_pMouseInput->GetLeft());
    }

    if (_type == GalGameUIType::Story && !_pUIPopUp->GetNowMode() &&
        _type != GalGameUIType::Item && _pScriptEngin->GetState() == amg::ScriptEngine::ScriptState::END) {
        _pUIGalStory->SetMousePoint(_pMouseInput->GetXNum(), _pMouseInput->GetYNum());
    }

    _pUIPopUp->SetMouse(_pMouseInput->GetXNum(), _pMouseInput->GetYNum());
    _pUIPopUp->SetLeft(_pMouseInput->GetLeft());

    //menuを押したとき処理
    if (_pUIGalMenuInit->GetSelect() == 1 && _pMouseInput->GetLeft()) {
        _pUIGalMenuInit->SetEnd(true);  //endの座標まで持っていく
        _pUIGalMenu->SetStart(true);  //startの座標までもっていく
        _type = GalGameUIType::Menu;
    }

    //cancelを押したとき処理
    if (_pUIGalMenu->GetSelectCancel() == 1 && _pMouseInput->GetLeft()) {
        _pUIGalMenu->SetEnd(true);  //外の座標までもっていく
        _pUIGalMenuInit->SetStart(true);  //中の座標まで持っていく
        _type = GalGameUIType::MenuIinit;

        _pUIGalStory->SetAddImageSize(1);
    }

    _pUIGalSetting->Process();
    //settingを押したとき処理
    if (_pUIGalMenu->GetSelectSetting() == 1 && _pMouseInput->GetLeft()) {
        _pUIGalSetting->SetStart(true);  //設定を開く
        _pUIGalSetting->SetNowMode(true);
        _type = GalGameUIType::Setting;
    }

    _pUIGalItem->Process();
    //itemを押したとき処理
    if (_pUIGalMenu->GetSelectItem() == 1 && _pMouseInput->GetLeft()) {
        _pUIGalItem->SetStart(true);  //設定を開く
        _pUIGalItem->SetNowMode(true);
        _type = GalGameUIType::Item;
    }

    if (_pDrunkTime->GetNowTime() == 0) {
        _sakeItem = false;
    }

    _pUIGalStory->Process();
    //storyを押したとき処理
    if (_pUIGalMenu->GetSelectStory() == 1 && _pMouseInput->GetLeft()) {
        _pUIGalStory->SetStart(true);  //設定を開く
        _pUIGalStory->SetNowMode(true);
        _type = GalGameUIType::Story;
    }

    //スクリプトエンジンxボタンの処理
    if (_pScriptEngin->GetState() != amg::ScriptEngine::ScriptState::END) {

        _scriptClose = _pCloselBScript->GetSelect();
        _pCloselBScript->SetSelect(Utility::ImageHitDetection(_pMouseInput->GetXNum(), _pMouseInput->GetYNum(), _pCloselBScript.get()));

        if (_scriptClose && !_pMouseInput->GetLeft()) {
            _scriptClose = false;
        }

        if (_scriptClose) {
            _pScriptEngin->SetState(amg::ScriptEngine::ScriptState::END);
        }
    }


    if (_type == GalGameUIType::Item && _pUIPopUp->GetNowMode() && _pUIGalItem->GetNowItemType() == 0) {
        //上ボタンの処理
        _upB = _pUpButton->GetSelect();
        _pUpButton->SetSelect(Utility::ImageHitDetection(_pMouseInput->GetXNum(), _pMouseInput->GetYNum(), _pUpButton.get()));

        if (_pMouseInput->GetTrgLeft() && _pUpButton->GetSelect() == 1) {
            if (_giveCoin >= 1000 && _giveCoin < 999999 ) {  //渡すお金をあげる
                _giveCoin += 10;
            }
        }

        //下ボタンの処理
        _downB = _pDownButton->GetSelect();
        _pDownButton->SetSelect(Utility::ImageHitDetection(_pMouseInput->GetXNum(), _pMouseInput->GetYNum(), _pDownButton.get()));

        if (_pDownButton->GetSelect() == 1 && _pMouseInput->GetTrgLeft()) {
            if (_giveCoin < 999999 && _giveCoin >= 1000) {  //渡すお金を下げる
                _giveCoin -= 10;
                if (_giveCoin < 1000) {
                    _giveCoin = 1000;
                }
            }
        }

        _pUIPopUp->SetPopString(_pUIGalItem->GetMoneyString());
    }


    if (_giveCoin != _pUIGalItem->GetGiveCoin()) {  //1回しかセットしない
        _pUIGalItem->SetGiveCoin(_giveCoin);
    }

    //ストーリーが始まっているなら全て閉じ状態   スクリプトエンジン閉じると立ち上がるので直す
    if (_pScriptEngin->GetState() != amg::ScriptEngine::ScriptState::END) {
        _pUIGalItem->StringAllFalse();
        _pUIGalStory->StringAllFalse();
        _pUIPopUp->SetNowMode(false);
        _pUIGalStory->SetEnd(true);
        _pUIGalStory->SetNowMode(false);
        _type = GalGameUIType::Menu;
    }

    
    _pUIGalMenuInit->Process();
    _pUIGalMenu->Process();

    _pDrunkTime->Process();

    _pScriptEngin->Update();
    _pCloselBScript->Process();
    _pUpButton->Process();
    _pDownButton->Process();
    _pMouseInput->LastProcess();

    _pUIGalMenu->SetCoin(_coin);

    _title = false;
    _downB = false;
    _upB = false;
}

void GalGameUI::SettingProcess() {

    if (_pUIGalSetting->GetComandSelect(0) && _pMouseInput->GetLeft()) {   //0=外出
        //外出モードに変更の処理

    }

    if (_pUIGalSetting->GetComandSelect(1) && _pMouseInput->GetLeft()) {  //1 = title
        //タイトルモードに変更の処理
        _title = true;
    }

    if (_pUIGalSetting->GetClose() == 1 && _pMouseInput->GetLeft()) {  //GetCloseがエリア外なのに1
        _pUIGalSetting->SetEnd(true);
        _pUIGalSetting->SetNowMode(false);
        _type = GalGameUIType::Menu;
    }
}

void GalGameUI::ItemProcess() {

    //金
    if (_pUIGalItem->GetComandSelect(0) && _pMouseInput->GetLeft()) {
        _pUIPopUp->SetNowMode(true);
        _pUIGalItem->SetMoneyStringDraw(true);
        _pUIPopUp->SetPopString(_pUIGalItem->GetMoneyString());
        _pUIGalItem->SetNowItemType(0);

        _pUpButton->SetDraw(0, true);
        _pUpButton->SetDraw(1, true);
        _pDownButton->SetDraw(0, true);
        _pDownButton->SetDraw(1, true);
    }

    if (_pUIPopUp->GetOk() && _pUIPopUp->GetLeft() && _pUIGalItem->GetNowItemType() == 0 && !_okFlag) {  //二回目に来ている
        if (_coin >= _giveCoin) {
            _coin -= _giveCoin;
            _okFlag = true;
        }
    }

    //酒
    if (_pUIGalItem->GetComandSelect(1) && _pMouseInput->GetLeft()) {
        _pUIPopUp->SetNowMode(true);
        _pUIGalItem->SetTequilaStringDraw(true);
        _pUIGalItem->SetNowItemType(1);

        _pUIPopUp->SetPopString(_pUIGalItem->GetTequilaString());
    }

    if (_pUIPopUp->GetOk() && _pUIPopUp->GetLeft() && _pDrunkTime->GetNowTime() == 0 &&
        _pUIGalItem->GetNowItemType() == 1) {
        _sakeItem = true;
        _pDrunkTime->SetStart(DRUNK_TIME);
    }

    if (_pUIGalItem->GetClose() == 1 && _pMouseInput->GetLeft()) {  //GetCloseがエリア外なのに1
        _pUIGalItem->SetEnd(true);
        _pUIGalItem->SetNowMode(false);
        _type = GalGameUIType::Menu;
    }
}

void GalGameUI::StoryProcess() {

    //0Story
    if (_pUIGalStory->GetComandSelect(0) && _pMouseInput->GetLeft()) { 
        _pUIPopUp->SetNowMode(true);
        _pUIGalStory->SetStory0StringDraw(true);

        _pUIPopUp->SetPopString(_pUIGalStory->GetStory0String());
    }

    if ( _pUIGalStory->GetStringType() == 0 && _pUIPopUp->GetOk() && _pUIPopUp->GetLeft()) {
        _pScriptEngin->ReInitialize();
        _pScriptEngin->SetState(amg::ScriptEngine::ScriptState::PARSING);
    }

    //1Story
    if (_pUIGalStory->GetComandSelect(1) && _pMouseInput->GetLeft()) { 
        _pUIPopUp->SetNowMode(true);

        _pUIGalStory->SetStory1StringDraw(true);

        _pUIPopUp->SetPopString(_pUIGalStory->GetStory1String());
    }

    //2Story
    if (_pUIGalStory->GetComandSelect(2) && _pMouseInput->GetLeft()) {  //1 = title
        _pUIPopUp->SetNowMode(true);

        _pUIGalStory->SetStory2StringDraw(true);

        _pUIPopUp->SetPopString(_pUIGalStory->GetStory2String());
    }

    //3Story
    if (_pUIGalStory->GetComandSelect(3) && _pMouseInput->GetLeft()) {  //1 = title
        _pUIPopUp->SetNowMode(true);

        _pUIGalStory->SetStory3StringDraw(true);

        _pUIPopUp->SetPopString(_pUIGalStory->GetStory3String());
    }

    //4Story
    if (_pUIGalStory->GetComandSelect(4) && _pMouseInput->GetLeft()) {  //1 = title
        _pUIPopUp->SetNowMode(true);

        _pUIGalStory->SetStory4StringDraw(true);

        _pUIPopUp->SetPopString(_pUIGalStory->GetStory4String());
    }

    if (_pUIGalStory->GetClose() == 1 && _pMouseInput->GetLeft()) {  //GetCloseがエリア外なのに1
        _pUIGalStory->SetEnd(true);
        _pUIGalStory->SetNowMode(false);
        _type = GalGameUIType::Menu;
    }
}

void GalGameUI::Draw() {

    _pMouseInput->Draw();
    _pUIGalSetting->Draw();
    _pUIGalStory->Draw();
    _pUIGalMenuInit->Draw();
    _pUIGalMenu->Draw();

    _pUIGalItem->Draw();

    if (_pUIPopUp->GetNowMode()) {
        if (_pUIPopUp->GetClose() && _pUIPopUp->GetLeft() || _pUIPopUp->GetOk() && _pUIPopUp->GetLeft()) {
            _pUIPopUp->SetNowMode(false);
            _pUIGalItem->StringAllFalse();
            _pUIGalStory->StringAllFalse();
            _pUpButton->SetDraw(0,false);
            _pUpButton->SetDraw(1, false);
            _pDownButton->SetDraw(0,false);
            _pDownButton->SetDraw(1, false);
            _okFlag = false;
        }
        _pUIPopUp->Draw();
    }

    if (_pScriptEngin->GetState() != amg::ScriptEngine::ScriptState::END) {
        _pScriptEngin->Render();
        _pCloselBScript->Draw();
    }

    _pDrunkTime->Draw();
    _pUpButton->Draw();
    _pDownButton->Draw();

   // DrawFormatString(20, 780, GetColor(255, 165, 0), "数字:%d",_favor);
    //DrawFormatString(20, 880, GetColor(255, 165, 0),"ber:%d",_molecule);

}

void GalGameUI::Terminate() {
    _pScriptEngin->Destroy();
}