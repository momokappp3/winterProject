#include "UIGalMenu.h"
#include "../../ResourceServer.h"
#include "../../Utility.h"
#include <array>

//#define PI 3.1415926535897932384626433832795f

UIGalMenu::UIGalMenu() {

    _pCancelSelectBase = nullptr;
	_pSettingSelectBase = nullptr;
	_pBstorySelectBase = nullptr;
	_pBitemSelectBase = nullptr;
	
	_pBarPinkBase = nullptr;
	_pBarRedBase = nullptr;

	_pCircleBase = nullptr;

	_pCoinBaseBase = nullptr;
	_pCoinNum = nullptr;
	_pTrustNum = nullptr;

	_pCancelInAndOut = nullptr;
	_pSettingInAndOut = nullptr;
	_pBstoryInAndOut = nullptr;
	_pBitemInAndOut = nullptr;

	_pBarPinkInAndOut = nullptr;
	_pBarRedInAndOut = nullptr;

	_pCircleInAndOut = nullptr;

	_pCoinBaseInAndOut = nullptr;
	_pCoinNumInAndOut = nullptr;
	_pTrustNumInAndOut = nullptr;
	
	//_pMoleculeTween = nullptr;

	_start = false;
	_end = false;

	 _cancel = -1;
	_setting = -1;
	_story = -1;
	_item = -1;

	_mouseX = -1;
	_mouseY = -1;

	_molecule = 0;
	_coin = -1;
	_favor = -1;

	_lastMolecule = 0;

}

UIGalMenu::~UIGalMenu() {
}

bool UIGalMenu::Init() {

	_pCancelSelectBase.reset(new UI2DSelectBase);
	_pSettingSelectBase.reset(new UI2DSelectBase);
	_pBstorySelectBase.reset(new UI2DSelectBase);
	_pBitemSelectBase.reset(new UI2DSelectBase);

	_pBarPinkBase.reset(new UIGauge);
	_pBarRedBase.reset(new UIGauge);

	_pCircleBase.reset(new UI2DBase);

	_pCoinBaseBase.reset(new UI2DBase);
	_pCoinNum.reset(new UINumber);
	_pTrustNum.reset(new UINumber);

	_pSettingInAndOut.reset(new UIInAndOut);
	_pCancelInAndOut.reset(new UIInAndOut);
	_pBstoryInAndOut.reset(new UIInAndOut);
	_pBitemInAndOut.reset(new UIInAndOut);

	_pBarPinkInAndOut.reset(new UIInAndOut);
	_pBarRedInAndOut.reset(new UIInAndOut);

	_pCircleInAndOut.reset(new UIInAndOut);

	_pCoinBaseInAndOut.reset(new UIInAndOut);
	_pCoinNumInAndOut.reset(new UIInAndOut);
	_pTrustNumInAndOut.reset(new UIInAndOut);

	//_pMoleculeTween.reset(new Tween);

	if (!DrawInit()) {  //画像のDrawInfo初期化処理
		return false;
	}

	if (!_pCancelInAndOut->Init() || !_pSettingInAndOut->Init() || !_pBstoryInAndOut->Init() ||
		!_pBitemInAndOut->Init() || !_pBarPinkInAndOut->Init() || !_pBarRedInAndOut->Init() ||
		!_pCircleInAndOut->Init() || !_pCoinBaseInAndOut->Init() || !_pCoinNumInAndOut->Init() ||
		!_pTrustNumInAndOut->Init()) {
		return false;
	}

	MoveInit();

	if (!_pBarPinkBase->Init(40) || !_pBarRedBase->Init(80)) {
		return false;
	}

	if (!_pCoinNum->Init(6) || !_pTrustNum->Init(2)) {
		return false;
	}

    return true;
}

void UIGalMenu::Process() {

	MoveProcess();

	_end = false;
	_start = false;

	if (_molecule == 30) {  //一回目は来る　2回目から来てない
		int o = 0;
	}

	if (!_pBarPinkBase->IsStart()) {
		if (_pBarPinkBase->GetNowRate() != _molecule) {
			_pBarPinkBase->SetRate(_molecule);
		}
	}

	_pBarRedBase->SetRate(100);

	_pCoinNum->SetNum(_coin);
	_pTrustNum->SetNum(_favor);

	_pCancelSelectBase->Process();
	_pSettingSelectBase->Process();
	_pBstorySelectBase->Process();
	_pBitemSelectBase->Process();

	_pBarPinkBase->Process();
	_pBarRedBase->Process();

	_pCircleBase->Process();

	_pCoinBaseBase->Process();
	_pCoinNum->Process();
	_pTrustNum->Process();

	_pCancelInAndOut->Process();
	_pSettingInAndOut->Process();
	_pBstoryInAndOut->Process();
	_pBitemInAndOut->Process();

	_pBarPinkInAndOut->Process();
	_pBarRedInAndOut->Process();

	_pCircleInAndOut->Process();

	_pCoinBaseInAndOut->Process();
	_pCoinNumInAndOut->Process();
	_pTrustNumInAndOut->Process();

}

void UIGalMenu::Draw() {

	_pCancelSelectBase->Draw();
	_pSettingSelectBase->Draw();
	_pBstorySelectBase->Draw();
	_pBitemSelectBase->Draw();

	_pBarPinkBase->Draw();
	_pBarRedBase->Draw();

	_pCircleBase->Draw();

	_pCoinBaseBase->Draw();
	_pCoinNum->Draw();
	_pTrustNum->Draw();
}

//================================================
bool UIGalMenu::DrawInit() {

	//×ボタン 差は180

	int handle = ResourceServer::LoadGraph("png/galUI/closeButton.png");
	int handle2 = ResourceServer::LoadGraph("png/galUI/closeButton_select.png");

	if (handle == -1 && handle2 == -1) {
		return false;
	}

	DrawInfo info = { handle,1870,10,true,1980,10 };
	DrawInfo info2 = { handle2,1870,10,true ,1980,10 };

	_pCancelSelectBase->SetDrawInfo(info);
	_pCancelSelectBase->SetDrawInfo(info2);

	//========================================================================
	//設定アイコン

	handle = ResourceServer::LoadGraph("png/galUI/setting.png");
	handle2 = ResourceServer::LoadGraph("png/galUI/setting_select.png");

	if (handle == -1 && handle2 == -1) {
		return false;
	}

	info = { handle,1800,20,true,1980,20 };
	info2 = { handle2,1800,20,true ,1980,20 };

	_pSettingSelectBase->SetDrawInfo(info);
	_pSettingSelectBase->SetDrawInfo(info2);

	//=========================================================================
	//ストーリーボタン

	handle = ResourceServer::LoadGraph("png/galUI/button_story_brack.png");
	handle2 = ResourceServer::LoadGraph("png/galUI/button_story_white.png");

	if (handle == -1 && handle2 == -1) {
		return false;
	}

	info = { handle,1625,30,true,1980,30 };
	info2 = { handle2,1625,30,true ,1980,30 };

	_pBstorySelectBase->SetDrawInfo(info);
	_pBstorySelectBase->SetDrawInfo(info2);

	//=========================================================================
	//アイテムボタン

	handle = ResourceServer::LoadGraph("png/galUI/button_item_black.png");
	handle2 = ResourceServer::LoadGraph("png/galUI/button_item_white.png");

	if (handle == -1 && handle2 == -1) {
		return false;
	}

	info = { handle,1450,30,true,1980,30 };
	info2 = { handle2,1450,30,true ,1980,30 };

	_pBitemSelectBase->SetDrawInfo(info);
	_pBitemSelectBase->SetDrawInfo(info2);

	//==========================================================================
	//体力ゲージPink 700*50

	handle = ResourceServer::LoadGraph("png/galUI/bar_base.png");
	handle2 = ResourceServer::LoadGraph("png/galUI/bar_pink.png");
	

	if (handle == -1 && handle2 == -1) {
		return false;
	}

	info = { handle,200,46,true,-760,46 };
	info2 = { handle2,200,46,true ,-760,46 };

	_pBarPinkBase->SetDrawInfo(info);
	_pBarPinkBase->SetDrawInfo(info2);


	//===========================================================================
	//体力ゲージRed  600*40

	handle = ResourceServer::LoadGraph("png/galUI/bar_base_2.png");
	handle2 = ResourceServer::LoadGraph("png/galUI/bar_red.png");

	if (handle == -1 && handle2 == -1) {
		return false;
	}

	info = { handle,160,137,true,-660,137 };
	info2 = { handle2,160,137,true ,-660,137 };

	_pBarRedBase->SetDrawInfo(info);
	_pBarRedBase->SetDrawInfo(info2);

	//=============================================================
	//サークル 430*430
	handle = ResourceServer::LoadGraph("png/galUI/uiCircle.png");

	if (handle == -1) {
		return false;
	}

	info = { handle,-136,-150,true,-430,-430 };

	_pCircleBase->SetDrawInfo(info);

	//==========================================================
	//CoinBase 215*52
	handle = ResourceServer::LoadGraph("png/galUI/number/coinBase.png");

	if (handle == -1) {
		return false;
	}

	info = { handle,10,10,true,-430,-430 };

	_pCoinBaseBase->SetDrawInfo(info);

	//======================================================
	//CoinNum
	std::array<int, 10> coinHandle{
		ResourceServer::LoadGraph("png/galUI/number/coin0.png"),
		ResourceServer::LoadGraph("png/galUI/number/coin1.png"),
		ResourceServer::LoadGraph("png/galUI/number/coin2.png"),
		ResourceServer::LoadGraph("png/galUI/number/coin3.png"),
		ResourceServer::LoadGraph("png/galUI/number/coin4.png"),
		ResourceServer::LoadGraph("png/galUI/number/coin5.png"),
		ResourceServer::LoadGraph("png/galUI/number/coin6.png"),
		ResourceServer::LoadGraph("png/galUI/number/coin7.png"),
		ResourceServer::LoadGraph("png/galUI/number/coin8.png"),
		ResourceServer::LoadGraph("png/galUI/number/coin9.png"),
	};

	//coinの位置はDrawでSetする

	for (int i = 0; i < 10; i++) {
		info = { coinHandle[i] ,175,18,true,-430,-430 };

		_pCoinNum->SetDrawInfo(info);
	}
	_pCoinNum->SetPoint({ 175,18 });

	//===============================================================
	//trustNum
	
	std::array<int, 10> trustHandle{
	ResourceServer::LoadGraph("png/galUI/number/trust0.png"),
	ResourceServer::LoadGraph("png/galUI/number/trust1.png"),
	ResourceServer::LoadGraph("png/galUI/number/trust2.png"),
	ResourceServer::LoadGraph("png/galUI/number/trust3.png"),
	ResourceServer::LoadGraph("png/galUI/number/trust4.png"),
	ResourceServer::LoadGraph("png/galUI/number/trust5.png"),
	ResourceServer::LoadGraph("png/galUI/number/trust6.png"),
	ResourceServer::LoadGraph("png/galUI/number/trust7.png"),
	ResourceServer::LoadGraph("png/galUI/number/trust8.png"),
	ResourceServer::LoadGraph("png/galUI/number/trust9.png"),
	};

	//数字の位置はSetでする

	for (int i = 0; i < 10; i++) {
		info = { trustHandle[i] ,110,85,true,-430,-430 };

		_pTrustNum->SetDrawInfo(info);
	}
	_pTrustNum->SetPoint({ 110,85 });

	return true;
}

void UIGalMenu::MoveInit() {

	//=====================================
	_pCancelSelectBase->SetRadius(20.0f);  //typeをサークルにしている

	DrawInfo infoInit;
	_pCancelSelectBase->GetDrawInfo(1, infoInit);

	_pCancelInAndOut->SetStartPosition(infoInit.startXY);
	_pCancelInAndOut->SetEndPosition(infoInit.xy);
	_pCancelInAndOut->SetNowPosition(infoInit.startXY);

	//=======================================
	//設定
	_pSettingSelectBase->SetRadius(50.0f);  //typeをサークルにしている

	_pSettingSelectBase->GetDrawInfo(0, infoInit);

	_pSettingInAndOut->SetStartPosition(infoInit.startXY);
	_pSettingInAndOut->SetEndPosition(infoInit.xy);
	_pSettingInAndOut->SetNowPosition(infoInit.startXY);

	//=======================================
	//スト―リ
	_pBstorySelectBase->SetRect();

	_pBstorySelectBase->GetDrawInfo(0, infoInit);

	_pBstoryInAndOut->SetStartPosition(infoInit.startXY);
	_pBstoryInAndOut->SetEndPosition(infoInit.xy);
	_pBstoryInAndOut->SetNowPosition(infoInit.startXY);
	 
	//=======================================
	//アイテム
	_pBitemSelectBase->SetRect();

	_pBitemSelectBase->GetDrawInfo(0, infoInit);

	_pBitemInAndOut->SetStartPosition(infoInit.startXY);
	_pBitemInAndOut->SetEndPosition(infoInit.xy);
	_pBitemInAndOut->SetNowPosition(infoInit.startXY);

	//=============================================
	//(当たり判定無いのでSetRadiusしなくてよい)
	//体力ゲージ上
	_pBarPinkBase->GetDrawInfo(0, infoInit);

	_pBarPinkInAndOut->SetStartPosition(infoInit.startXY);
	_pBarPinkInAndOut->SetEndPosition(infoInit.xy);
	_pBarPinkInAndOut->SetNowPosition(infoInit.startXY);

	//===========================================
	//体力ゲージ下
	_pBarRedBase->GetDrawInfo(0, infoInit);

	_pBarRedInAndOut->SetStartPosition(infoInit.startXY);  //ここをセットしないといけない
	_pBarRedInAndOut->SetEndPosition(infoInit.xy);
	_pBarRedInAndOut->SetNowPosition(infoInit.startXY);

	//=============================================
	//サークル
	_pCircleBase->GetDrawInfo(0, infoInit);

	_pCircleInAndOut->SetStartPosition(infoInit.startXY);
	_pCircleInAndOut->SetEndPosition(infoInit.xy);
	_pCircleInAndOut->SetNowPosition(infoInit.startXY);

	//=============================================
	//CoinBase
	_pCoinBaseBase->GetDrawInfo(0, infoInit);

	_pCoinBaseInAndOut->SetStartPosition(infoInit.startXY);
	_pCoinBaseInAndOut->SetEndPosition(infoInit.xy);
	_pCoinBaseInAndOut->SetNowPosition(infoInit.startXY);

	//=============================================
	//CoinNum
	_pCoinNum->GetDrawInfo(0, infoInit);

	_pCoinNumInAndOut->SetStartPosition(infoInit.startXY);
	_pCoinNumInAndOut->SetEndPosition(infoInit.xy);
	_pCoinNumInAndOut->SetNowPosition(infoInit.startXY);

	//=============================================
	//TrustNum
	_pTrustNum->GetDrawInfo(0, infoInit);

	_pTrustNumInAndOut->SetStartPosition(infoInit.startXY);
	_pTrustNumInAndOut->SetEndPosition(infoInit.xy);
	_pTrustNumInAndOut->SetNowPosition(infoInit.startXY);

}

void UIGalMenu::MoveProcess() {

	_cancel = _pCancelSelectBase->GetSelect();

	_pCancelSelectBase->SetPoint(0, _pCancelInAndOut->GetNowPosition());
	_pCancelSelectBase->SetPoint(1, _pCancelInAndOut->GetNowPosition());

	_pCancelInAndOut->SetIsEnd(_end);
	_pCancelInAndOut->SetIsStart(_start);

	_pCancelSelectBase->SetSelect(Utility::ImageHitDetection(_mouseX, _mouseY, _pCancelSelectBase.get()));

	//================================================
	//設定
	_setting = _pSettingSelectBase->GetSelect();

	_pSettingSelectBase->SetPoint(0, _pSettingInAndOut->GetNowPosition());
	_pSettingSelectBase->SetPoint(1, _pSettingInAndOut->GetNowPosition());

	_pSettingInAndOut->SetIsEnd(_end);
	_pSettingInAndOut->SetIsStart(_start);

	_pSettingSelectBase->SetSelect(Utility::ImageHitDetection(_mouseX, _mouseY, _pSettingSelectBase.get()));

	//================================================
	//ストーリー
	_story = _pBstorySelectBase->GetSelect();

	_pBstorySelectBase->SetPoint(0, _pBstoryInAndOut->GetNowPosition());
	_pBstorySelectBase->SetPoint(1, _pBstoryInAndOut->GetNowPosition());

	_pBstoryInAndOut->SetIsEnd(_end);
	_pBstoryInAndOut->SetIsStart(_start);

	_pBstorySelectBase->SetSelect(Utility::ImageHitDetection(_mouseX, _mouseY, _pBstorySelectBase.get()));

	//===============================================
	//アイテム
	_item = _pBitemSelectBase->GetSelect();

	_pBitemSelectBase->SetPoint(0, _pBitemInAndOut->GetNowPosition());
	_pBitemSelectBase->SetPoint(1, _pBitemInAndOut->GetNowPosition());

	_pBitemInAndOut->SetIsEnd(_end);
	_pBitemInAndOut->SetIsStart(_start);

	_pBitemSelectBase->SetSelect(Utility::ImageHitDetection(_mouseX, _mouseY, _pBitemSelectBase.get()));

	//===============================================
	//体力pink

	_pBarPinkBase->SetPoint(0, _pBarPinkInAndOut->GetNowPosition());
	_pBarPinkBase->SetPoint(1, _pBarPinkInAndOut->GetNowPosition());
	_pBarPinkInAndOut->SetIsEnd(_end);
	_pBarPinkInAndOut->SetIsStart(_start);

	//体力red
	_pBarRedBase->SetPoint(0, _pBarRedInAndOut->GetNowPosition());
	_pBarRedBase->SetPoint(1, _pBarRedInAndOut->GetNowPosition());
	_pBarRedInAndOut->SetIsEnd(_end);
	_pBarRedInAndOut->SetIsStart(_start);

	//===============================================
	//サークル

	_pCircleBase->SetPoint(0, _pCircleInAndOut->GetNowPosition());


	/*
	回転の処理
	*/

	_pCircleInAndOut->SetIsEnd(_end);
	_pCircleInAndOut->SetIsStart(_start);


	//=================================================================
	//coinBase
	_pCoinBaseBase->SetPoint(0, _pCoinBaseInAndOut->GetNowPosition());

	_pCoinBaseInAndOut->SetIsEnd(_end);
	_pCoinBaseInAndOut->SetIsStart(_start);

	//================================================================
	//coinNum
	_pCoinNum->SetPoint(_pCoinNumInAndOut->GetNowPosition());

	_pCoinNumInAndOut->SetIsEnd(_end);
	_pCoinNumInAndOut->SetIsStart(_start);

	//===============================================================
	//trustNum
	_pTrustNum->SetPoint(_pTrustNumInAndOut->GetNowPosition());

	_pTrustNumInAndOut->SetIsEnd(_end);
	_pTrustNumInAndOut->SetIsStart(_start);
}