#include "RoomGameUI.h"
#include "../ApplicationMain.h"
#include "../Mode/ModeTitle.h"
#include "../Mode/RoomGame.h"
#include "../../Utility.h"

const int DRUNK_TIME = 10;

RoomGameUI::RoomGameUI() {

    _type = RoomGameUIType::Max;

    _pUIRoomMenuInit = nullptr;
    _pUIRoomMenu = nullptr;
    _pUIRoomSetting = nullptr;
    _pUIRoomItem = nullptr;
    _pUIRoomStory = nullptr;
    _pSoundManager = nullptr;

    _pUIPopUp = nullptr;
    _pDrunkTime = nullptr;
    _pScriptEngin = nullptr;
    _pMouseInput = nullptr;

    _faceInfo = {0, 0.0, 0.0, 0, 0,0};

    _pCloselBScript = nullptr;
    _pUpButton = nullptr;
    _pDownButton = nullptr;

    _sakeItem = false;
    _goTitle = false;
    _goAction = false;

    _scriptClose = false;
    _upB = false;
    _downB = false;

    _okFlag = false;
    _isFaceInfo = false;

    _pPlayerInfo = nullptr;

    _giveCoin = 0;
}

RoomGameUI::~RoomGameUI() {
}

bool RoomGameUI::Init(std::shared_ptr<SoundManager>& soundManager, std::shared_ptr<PlayerInfo>& playerInfo) {

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

    if (playerInfo == nullptr) {
        return false;
    }

    _pPlayerInfo = playerInfo;

    _type = RoomGameUIType::MenuIinit;

    _pUIRoomMenuInit.reset(new UIRoomMenuInit);
    _pUIRoomMenu.reset(new UIRoomMenu);
    _pUIRoomSetting.reset(new UIRoomSetting);
    _pUIRoomItem.reset(new UIRoomItem);
    _pUIRoomStory.reset(new UIRoomStory);

    _pUIPopUp.reset(new UIPopUp);
    _pDrunkTime.reset(new UITime);
    _pScriptEngin.reset(new amg::ScriptEngine);
    _pMouseInput.reset(new MouseInput);

    _pCloselBScript.reset(new UI2DSelectBase);
    _pUpButton.reset(new UI2DSelectBase);
    _pDownButton.reset(new UI2DSelectBase);

    if (!_pUIRoomMenu->Init(_pSoundManager, _pPlayerInfo) || !_pUIRoomMenuInit->Init(_pSoundManager) || !_pUIRoomItem->Init(_pSoundManager) ||
        !_pUIRoomSetting->Init(_pSoundManager) || !_pUIRoomStory->Init(_pSoundManager) || !_pUIPopUp->Init(_pSoundManager)) {  //�~false�ɗ��Ă���
        return false;
    }

    //x�{�^��
    int handle = ResourceServer::LoadGraph("png/RoomUI/closeButton.png");
    int handle2 = ResourceServer::LoadGraph("png/RoomUI/closeButton_select.png");

    if (handle == -1 && handle2 == -1) {
        return false;
    }

    DrawInfo info = { handle,412,270,true };
    DrawInfo info2 = { handle2,412,270,true };

    _pCloselBScript->SetDrawInfo(info);
    _pCloselBScript->SetDrawInfo(info2);
    _pCloselBScript->SetRadius(20);

    //����
    handle = ResourceServer::LoadGraph("png/RoomUI/use/arrowUp.png");
    handle2 = ResourceServer::LoadGraph("png/RoomUI/use/arrowUpSelect.png");

    if (handle == -1 && handle2 == -1) {
        return false;
    }

    info = { handle,1700,400,false};
    info2 = { handle2,1700,400,false };

    _pUpButton->SetDrawInfo(info);
    _pUpButton->SetDrawInfo(info2);
    _pUpButton->SetRect();

    //�����
    handle = ResourceServer::LoadGraph("png/RoomUI/use/arrowDown.png");
    handle2 = ResourceServer::LoadGraph("png/RoomUI/use/arrowDownSelect.png");

    if (handle == -1 && handle2 == -1) {
        return false;
    }

    info = { handle,1700,515,false };
    info2 = { handle2,1700,515,false };

    _pDownButton->SetDrawInfo(info);
    _pDownButton->SetDrawInfo(info2);
    _pDownButton->SetRect();


    if (!_pScriptEngin->Initialize("source/excel/test.json",_pPlayerInfo)) {
        return false;
    }

    if (!_pDrunkTime->Init(99, 2)) {
        return false;
    }

    _pScriptEngin->SetState(amg::ScriptEngine::ScriptState::END);

    _giveCoin = 2500;

    auto onSelect = [this]() {
        //�T�E���h�炷
        _pSoundManager->PlaySECommon(SoundManager::SECommon::Select);
    };

    _pUpButton->SetOnSelect(onSelect);
    _pDownButton->SetOnSelect(onSelect);
    _pCloselBScript->SetOnSelect(onSelect);

    return true;
}

void RoomGameUI::Process() {

    _pMouseInput->Process();
    _pUIPopUp->Process();
    /*
    if (_pScriptEngin->IsFavor()) {
        
        int getNowFavor = 0;
        
        getNowFavor = _pScriptEngin->GetFavor();  //���q9900�܂�

        
        += getNowFavor / 100;
        _molecule = getNowFavor % 100;
        
    }
    
    if (_molecule >= 9900) {
        _molecule = 9900;
    }
    */

    //_pUIRoomMenu->SetFavor(_favor);
    //_pUIRoomMenu->SetMolecule(_pScriptEngin->IsFavor());  //???????
    /*
    if (_pScriptEngin->IsFavor()) {

        int getNowFavor = 0;

        getNowFavor = _pPlayerInfo->GetFavor();

        //_favor += getNowFavor;
        _pPlayerInfo->SetFavor(getNowFavor, true);
    }
    */

    if (_pScriptEngin->IsGetFace()) {
        _isFaceInfo = true;
        _faceInfo = _pScriptEngin->GetFace();
    }

    if (_type == RoomGameUIType::Setting) {
        SettingProcess();
    }

    if (_type == RoomGameUIType::Item) {
        ItemProcess();
    }

    if (_type == RoomGameUIType::Story) {
        StoryProcess();
    }

    if (_type == RoomGameUIType::MenuIinit) {
        _pUIRoomMenuInit->SetMousePoint(_pMouseInput->GetXNum(), _pMouseInput->GetYNum());
    }

    if (_type == RoomGameUIType::Menu && _type!=RoomGameUIType::Item && _type != RoomGameUIType::Story && 
        _type != RoomGameUIType::Item && _pScriptEngin->GetState() == amg::ScriptEngine::ScriptState::END) {

        _pUIRoomMenu->SetMousePoint(_pMouseInput->GetXNum(), _pMouseInput->GetYNum());
    }

    if (_type == RoomGameUIType::Setting && _type != RoomGameUIType::Item && _type != RoomGameUIType::Story &&
        _pMouseInput->GetYNum() && _pScriptEngin->GetState() == amg::ScriptEngine::ScriptState::END) {

        _pUIRoomSetting->SetMousePoint(_pMouseInput->GetXNum(), _pMouseInput->GetYNum());
        _pUIRoomMenu->SetSelectSetting(0);  //�������̂Ƃ�����N���b�N���Ă��邽��
    }

    if (_type == RoomGameUIType::Item && _type != RoomGameUIType::Story && _pScriptEngin->GetState() == amg::ScriptEngine::ScriptState::END) {

        _pUIRoomItem->SetMousePoint(_pMouseInput->GetXNum(), _pMouseInput->GetYNum());
        _pUIRoomItem->SetMouseLeft(_pMouseInput->GetLeft());
        _pUIRoomMenu->SetSelectItem(0);   //�������̂Ƃ�����N���b�N���Ă��邽��
    }

    if (_type == RoomGameUIType::Story && !_pUIPopUp->GetNowMode() &&
        _type != RoomGameUIType::Item && _pScriptEngin->GetState() == amg::ScriptEngine::ScriptState::END) {

        _pUIRoomStory->SetMousePoint(_pMouseInput->GetXNum(), _pMouseInput->GetYNum());
        _pUIRoomMenu->SetSelectSetting(0);  //�������̂Ƃ�����N���b�N���Ă��邽��
    }

    _pUIPopUp->SetMouse(_pMouseInput->GetXNum(), _pMouseInput->GetYNum());
    _pUIPopUp->SetTrgLeft(_pMouseInput->GetTrgLeft());

    //menu���������Ƃ�����
    if (_pUIRoomMenuInit->GetSelect() == 1 && _pMouseInput->GetTrgLeft()) {
        _pUIRoomMenuInit->SetEnd(true);  //end�̍��W�܂Ŏ����Ă���
        _pUIRoomMenu->SetStart(true);  //start�̍��W�܂ł����Ă���
        _type = RoomGameUIType::Menu;
        _pSoundManager->PlaySECommon(SoundManager::SECommon::OK);
    }

    //cancel���������Ƃ�����
    if (_pUIRoomMenu->GetSelectCancel() == 1 && _pMouseInput->GetTrgLeft()) {
        _pUIRoomMenu->SetEnd(true);  //�O�̍��W�܂ł����Ă���
        _pUIRoomMenuInit->SetStart(true);  //���̍��W�܂Ŏ����Ă���
        _type = RoomGameUIType::MenuIinit;

        _pUIRoomStory->SetAddImageSize(1);
        _pSoundManager->PlaySECommon(SoundManager::SECommon::Cancel);
    }

    _pUIRoomSetting->Process();
    //setting���������Ƃ�����
    if (_pUIRoomMenu->GetSelectSetting() == 1 && _pMouseInput->GetTrgLeft()) {
        _pUIRoomSetting->SetStart(true);  //�ݒ���J��
        _pUIRoomSetting->SetNowMode(true);
        _type = RoomGameUIType::Setting;
         _pSoundManager->PlaySECommon(SoundManager::SECommon::OK);
    }

    _pUIRoomItem->Process();
    //item���������Ƃ�����
    if (_pUIRoomMenu->GetSelectItem() == 1 && _pMouseInput->GetTrgLeft()) {
        _pUIRoomItem->SetStart(true);  //�ݒ���J��
        _pUIRoomItem->SetNowMode(true);
        _type = RoomGameUIType::Item;
        _pSoundManager->PlaySECommon(SoundManager::SECommon::OK);
    }
    
    //���̉����鏈��
    if (_sakeItem && _pDrunkTime->GetNowTime() == 1) {
        _sakeItem = false;
        _pPlayerInfo->SetMentalNum(30, false);
        _pSoundManager->PlaySECommon(SoundManager::SECommon::BarDown,100);
    }
    

    if (_pDrunkTime->GetEndNow()) {
        _sakeItem = false;
        _pPlayerInfo->SetMentalNum(30, false);
        _pSoundManager->PlaySECommon(SoundManager::SECommon::BarDown, 100);
    }

    _pUIRoomStory->Process();
    //story���������Ƃ�����
    if (_pUIRoomMenu->GetSelectStory() == 1 && _pMouseInput->GetTrgLeft()) {
        _pUIRoomStory->SetStart(true);  //�ݒ���J��
        _pUIRoomStory->SetNowMode(true);
        _type = RoomGameUIType::Story;
        _pSoundManager->PlaySECommon(SoundManager::SECommon::OK);
    }

    //�X�N���v�g�G���W��x�{�^���̏���
    if (_pScriptEngin->GetState() != amg::ScriptEngine::ScriptState::END) {

        _scriptClose = _pCloselBScript->GetSelect();
        _pCloselBScript->SetSelect(Utility::ImageHitDetection(_pMouseInput->GetXNum(), _pMouseInput->GetYNum(), _pCloselBScript.get()));

        if (_scriptClose && !_pMouseInput->GetTrgLeft()) {
            _scriptClose = false;
        }

        if (_scriptClose) {
            _pScriptEngin->SetState(amg::ScriptEngine::ScriptState::END);
            _pSoundManager->PlaySECommon(SoundManager::SECommon::Cancel);
        }
    }

    if (_type == RoomGameUIType::Item && _pUIPopUp->GetNowMode() && _pUIRoomItem->GetNowItemType() == 0) {
        //��{�^���̏���
        _upB = _pUpButton->GetSelect();
        _pUpButton->SetSelect(Utility::ImageHitDetection(_pMouseInput->GetXNum(), _pMouseInput->GetYNum(), _pUpButton.get()));

        if (_pMouseInput->GetLeft() && _pUpButton->GetSelect() == 1) {
            if (_giveCoin >= 1000 && _giveCoin < 999999 ) {  //�n��������������
                _giveCoin += 10;
            }
        }

        //���{�^���̏���
        _downB = _pDownButton->GetSelect();
        _pDownButton->SetSelect(Utility::ImageHitDetection(_pMouseInput->GetXNum(), _pMouseInput->GetYNum(), _pDownButton.get()));

        if (_pDownButton->GetSelect() == 1 && _pMouseInput->GetLeft()) {
            if (_giveCoin < 999999 && _giveCoin >= 1000) {  //�n��������������
                _giveCoin -= 10;
                if (_giveCoin < 1000) {
                    _giveCoin = 1000;
                    _pSoundManager->PlaySECommon(SoundManager::SECommon::OK);
                }
            }
        }
        _pUIPopUp->SetPopString(_pUIRoomItem->GetMoneyString());
    }

    if (_giveCoin != _pUIRoomItem->GetGiveCoin()) {  //1�񂵂��Z�b�g���Ȃ�
        _pUIRoomItem->SetGiveCoin(_giveCoin);
    }

    //�X�g�[���[���n�܂��Ă���Ȃ�S�ĕ����   �X�N���v�g�G���W������Ɨ����オ��̂Œ���
    if (_pScriptEngin->GetState() != amg::ScriptEngine::ScriptState::END) {
        _pUIRoomItem->StrinRoomlFalse();
        _pUIRoomStory->StrinRoomlFalse();
        _pUIPopUp->SetNowMode(false);
        _pUIRoomStory->SetEnd(true);
        _pUIRoomStory->SetNowMode(false);
        _type = RoomGameUIType::Menu;
        _pSoundManager->PlaySECommon(SoundManager::SECommon::Cancel);
    }

    _pUIRoomMenuInit->Process();
    _pDrunkTime->Process();
    _pUIRoomMenu->Process();
    _pScriptEngin->Update();
    _pCloselBScript->Process();
    _pUpButton->Process();
    _pDownButton->Process();
    _pMouseInput->LastProcess();
    _pSoundManager->Process();
    _pPlayerInfo->Process();

    _downB = false;
    _upB = false;
}

void RoomGameUI::SettingProcess() {

    if (_pUIRoomSetting->GetComandSelect(0) && _pMouseInput->GetTrgLeft()) {   //0=�O�o
        //�O�o���[�h�ɕύX�̏���
        _goAction = true;
        _pSoundManager->PlaySECommon(SoundManager::SECommon::OK2);
    }

    if (_pUIRoomSetting->GetComandSelect(1) && _pMouseInput->GetTrgLeft()) {  //1 = title
        //�^�C�g�����[�h�ɕύX�̏���
        _goTitle = true;
        _pSoundManager->PlaySECommon(SoundManager::SECommon::OK2);
    }

    if (_pUIRoomSetting->GetClose() == 1 && _pMouseInput->GetTrgLeft()) {
        _pUIRoomSetting->SetEnd(true);
        _pUIRoomSetting->SetNowMode(false);
        _type = RoomGameUIType::Menu;
        _pSoundManager->PlaySECommon(SoundManager::SECommon::Cancel);
    }
}

void RoomGameUI::ItemProcess() {

    //��
    if (_pUIRoomItem->GetComandSelect(0) && _pMouseInput->GetTrgLeft()) {
        _pUIPopUp->SetNowMode(true);
        _pUIRoomItem->SetMoneyStringDraw(true);
        _pUIPopUp->SetPopString(_pUIRoomItem->GetMoneyString());
        _pUIRoomItem->SetNowItemType(0);

        _pUpButton->SetDraw(0, true);
        _pUpButton->SetDraw(1, true);
        _pDownButton->SetDraw(0, true);
        _pDownButton->SetDraw(1, true);

        _pSoundManager->PlaySECommon(SoundManager::SECommon::OK);
    }

    if (_pUIPopUp->GetOk() && _pUIPopUp->GetTrgLeft() && _pUIRoomItem->GetNowItemType() == 0 && !_okFlag) {  //���ڂɗ��Ă���
        if ( _pPlayerInfo->GetCoin() >= _giveCoin) {
            _pPlayerInfo->SetCoin(_giveCoin, false);
            _okFlag = true;
            _pSoundManager->PlaySECommon(SoundManager::SECommon::OK2);

            //_pUIRoomMenu->PlusMentalNum(10);  //�Ƃ肠����

            _pPlayerInfo->SetMentalNum(10, true);

            _kaneOK = true;

        }
        else {
            _pSoundManager->PlaySECommon(SoundManager::SECommon::Mistake);
            _kaneNo = true;
        }
    }

    //��
    if (_pUIRoomItem->GetComandSelect(1) && _pMouseInput->GetTrgLeft()) {
        _pUIPopUp->SetNowMode(true);
        _pUIRoomItem->SetTequilaStringDraw(true);
        _pUIRoomItem->SetNowItemType(1);

        _pUIPopUp->SetPopString(_pUIRoomItem->GetTequilaString());
        _pSoundManager->PlaySECommon(SoundManager::SECommon::OK);
    }

    if (_pUIPopUp->GetOk() && _pUIPopUp->GetTrgLeft() && _pDrunkTime->GetNowTime() == 0 &&
        _pUIRoomItem->GetNowItemType() == 1) {
        _sakeItem = true;
        _pDrunkTime->SetStart(DRUNK_TIME);
        _pSoundManager->PlaySECommon(SoundManager::SECommon::OK2);

        _pPlayerInfo->SetMentalNum(30, true);
    }

    if (_pUIRoomItem->GetClose() == 1 && _pMouseInput->GetTrgLeft()) {
        _pUIRoomItem->SetEnd(true);
        _pUIRoomItem->SetNowMode(false);
        _type = RoomGameUIType::Menu;
        _pSoundManager->PlaySECommon(SoundManager::SECommon::Cancel);
    }
}

void RoomGameUI::StoryProcess() {

    //0Story
    if (_pUIRoomStory->GetComandSelect(0) && _pMouseInput->GetTrgLeft()) { 
        _pUIPopUp->SetNowMode(true);
        _pUIRoomStory->SetStory0StringDraw(true);

        _pUIPopUp->SetPopString(_pUIRoomStory->GetStory0String());
        _pSoundManager->PlaySECommon(SoundManager::SECommon::OK);
    }

    //1Story
    if (_pUIRoomStory->GetComandSelect(1) && _pMouseInput->GetTrgLeft()) { 
        _pUIPopUp->SetNowMode(true);

        _pUIRoomStory->SetStory1StringDraw(true);

        _pUIPopUp->SetPopString(_pUIRoomStory->GetStory1String());
        _pSoundManager->PlaySECommon(SoundManager::SECommon::OK);
    }

    //2Story
    if (_pUIRoomStory->GetComandSelect(2) && _pMouseInput->GetTrgLeft()) {  //1 = title
        _pUIPopUp->SetNowMode(true);

        _pUIRoomStory->SetStory2StringDraw(true);

        _pUIPopUp->SetPopString(_pUIRoomStory->GetStory2String());
        _pSoundManager->PlaySECommon(SoundManager::SECommon::OK);
    }

    //3Story
    if (_pUIRoomStory->GetComandSelect(3) && _pMouseInput->GetTrgLeft()) {  //1 = title
        _pUIPopUp->SetNowMode(true);

        _pUIRoomStory->SetStory3StringDraw(true);

        _pUIPopUp->SetPopString(_pUIRoomStory->GetStory3String());
        _pSoundManager->PlaySECommon(SoundManager::SECommon::OK);
    }

    //4Story
    if (_pUIRoomStory->GetComandSelect(4) && _pMouseInput->GetTrgLeft()) {  //1 = title
        _pUIPopUp->SetNowMode(true);

        _pUIRoomStory->SetStory4StringDraw(true);

        _pUIPopUp->SetPopString(_pUIRoomStory->GetStory4String());
        _pSoundManager->PlaySECommon(SoundManager::SECommon::OK);
    }

    //PopUpOK
    if (_pUIRoomStory->GetStringType() == 0 && _pUIPopUp->GetOk() && _pUIPopUp->GetTrgLeft()) {
        _pScriptEngin->ReInitialize();
        _pScriptEngin->SetState(amg::ScriptEngine::ScriptState::PARSING);
        _pSoundManager->PlaySECommon(SoundManager::SECommon::OK2);
    }

    //PopUpClose
    if (_pUIRoomStory->GetClose() == 1 && _pMouseInput->GetTrgLeft()) {
        _pUIRoomStory->SetEnd(true);
        _pUIRoomStory->SetNowMode(false);
        _type = RoomGameUIType::Menu;
        _pSoundManager->PlaySECommon(SoundManager::SECommon::Cancel);
    }
}

void RoomGameUI::Draw() {

    _pMouseInput->Draw();
    _pUIRoomSetting->Draw();
    _pUIRoomStory->Draw();
    _pUIRoomMenuInit->Draw();
    _pUIRoomMenu->Draw();

    _pUIRoomItem->Draw();

    if (_pUIPopUp->GetNowMode()) {
        if (_pUIPopUp->GetClose() && _pUIPopUp->GetTrgLeft() || _pUIPopUp->GetOk() && _pUIPopUp->GetTrgLeft()) {
            if (_pUIPopUp->GetClose()) {
                _pSoundManager->PlaySECommon(SoundManager::SECommon::Cancel);
            }
            _pUIPopUp->SetNowMode(false);
            _pUIRoomItem->StrinRoomlFalse();
            _pUIRoomStory->StrinRoomlFalse();
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

   //DrawFormatString(20, 780, GetColor(255, 165, 0), "GameUI����:%d",_pPlayerInfo->GetMentalNum());
   // DrawFormatString(20, 880, GetColor(255, 165, 0),"GameUIber:%d",_molecule);
}

void RoomGameUI::Terminate() {
    _pScriptEngin->Destroy();
}