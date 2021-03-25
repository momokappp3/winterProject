#include "GalGameUI.h"

GalGameUI::GalGameUI() {

    _type = GalGameUIType::Max;

    _pUIGalMenuInit = nullptr;
    _pUIGalMenu = nullptr;
    _pUIGalSetting = nullptr;
    _pUIGalItem = nullptr;
    _pUIGalStory = nullptr;

    _pMouseInput = nullptr;
}

GalGameUI::~GalGameUI() {
}

bool GalGameUI::Init() {

    _type = GalGameUIType::MenuIinit;

    _pUIGalMenuInit.reset(new UIGalMenuInit);
    _pUIGalMenu.reset(new UIGalMenu);
    _pUIGalSetting.reset(new UIGalSetting);
    _pUIGalItem.reset(new UIGalItem);
    _pUIGalStory.reset(new UIGalStory);

    _pMouseInput.reset(new MouseInput);

    if (!_pUIGalMenu->Init() || !_pUIGalMenuInit->Init() || !_pUIGalItem->Init() ||
        !_pUIGalSetting->Init() || !_pUIGalStory->Init()) {
        return false;
    }

    return true;
}

void GalGameUI::Process() {

    _pMouseInput->Process();

    _pUIGalMenu->SetCoin(_coin);
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

    if (_type == GalGameUIType::Menu && _type!=GalGameUIType::Item && _type != GalGameUIType::Story) {
        _pUIGalMenu->SetMousePoint(_pMouseInput->GetXNum(), _pMouseInput->GetYNum());
    }

    if (_type == GalGameUIType::Setting && _type != GalGameUIType::Item && _type != GalGameUIType::Story) {
        _pUIGalSetting->SetMousePoint(_pMouseInput->GetXNum(), _pMouseInput->GetYNum());
    }

    if (_type == GalGameUIType::Item && _type != GalGameUIType::Story) {
        _pUIGalItem->SetMousePoint(_pMouseInput->GetXNum(), _pMouseInput->GetYNum());
        _pUIGalItem->SetMouseLeft(_pMouseInput->GetLeft());
    }

    if (_type == GalGameUIType::Story && _type != GalGameUIType::Item) {
        _pUIGalStory->SetMousePoint(_pMouseInput->GetXNum(), _pMouseInput->GetYNum());
    }

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

    _pUIGalStory->Process();
    //storyを押したとき処理
    if (_pUIGalMenu->GetSelectStory() == 1 && _pMouseInput->GetLeft()) {
        _pUIGalStory->SetStart(true);  //設定を開く
        _pUIGalStory->SetNowMode(true);
        _type = GalGameUIType::Story;
    }

    _pUIGalMenuInit->Process();
    _pUIGalMenu->Process();

}

void GalGameUI::SettingProcess() {

    if (_pUIGalSetting->GetComandSelect(0) && _pMouseInput->GetLeft()) {   //0=外出
        //外出モードに変更の処理

    }

    if (_pUIGalSetting->GetComandSelect(1) && _pMouseInput->GetLeft()) {  //1 = title
        //タイトルモードに変更の処理
    }

    if (_pUIGalSetting->GetClose() == 1 && _pMouseInput->GetLeft()) {  //GetCloseがエリア外なのに1
        _pUIGalSetting->SetEnd(true);
        _pUIGalSetting->SetNowMode(false);
        _type = GalGameUIType::Menu;
    }
}

void GalGameUI::ItemProcess() {

    if (_pUIGalItem->GetComandSelect(0) && _pMouseInput->GetLeft()) {   //0=外出
        //お金使用の処理

    }

    if (_pUIGalItem->GetComandSelect(1) && _pMouseInput->GetLeft()) {  //1 = title
        //酒使用の処理
    }

    if (_pUIGalItem->GetClose() == 1 && _pMouseInput->GetLeft()) {  //GetCloseがエリア外なのに1
        _pUIGalItem->SetEnd(true);
        _pUIGalItem->SetNowMode(false);
        _type = GalGameUIType::Menu;
    }
}

void GalGameUI::StoryProcess() {

    if (_pUIGalStory->GetComandSelect(0) && _pMouseInput->GetLeft()) {  //1 = title
    //story選択処理
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
    _pUIGalItem->Draw();
    _pUIGalMenuInit->Draw();
    _pUIGalMenu->Draw();
}