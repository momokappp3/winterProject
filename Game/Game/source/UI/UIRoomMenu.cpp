#include "UIRoomMenu.h"
#include "../../ResourceServer.h"
#include "../../Utility.h"
#include <array>

UIRoomMenu::UIRoomMenu() {

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
	
	_pSoundManager = nullptr;
	//_pMoleculeTween = nullptr;
	
	_start = false;
	_end = false;

	 _cancel = -1;
	_setting = -1;
	_story = -1;
	_item = -1;

	_mouseX = -1;
	_mouseY = -1;

	_lastMolecule = 0;
	_lastMentalNum = 0;
}

UIRoomMenu::~UIRoomMenu() {
}

bool UIRoomMenu::Init(std::shared_ptr<SoundManager>& soundManager, std::shared_ptr<PlayerInfo>& playerInfo) {

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

	_lastMentalNum = _pPlayerInfo->GetMentalNum();

	_pCancelSelectBase.reset(new UI2DSelectBase);
	_pSettingSelectBase.reset(new UI2DSelectBase);
	_pBstorySelectBase.reset(new UI2DSelectBase);
	_pBitemSelectBase.reset(new UI2DSelectBase);

	_pBarPinkBase.reset(new LevelUpGauge);
	_pBarRedBase.reset(new MentalGauge);

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

	if (!DrawInit()) {  //�摜��DrawInfo����������  false�ɗ��Ă���
		return false;
	}

	if (!_pCancelInAndOut->Init() || !_pSettingInAndOut->Init() || !_pBstoryInAndOut->Init() ||
		!_pBitemInAndOut->Init() || !_pBarPinkInAndOut->Init() || !_pBarRedInAndOut->Init() ||
		!_pCircleInAndOut->Init() || !_pCoinBaseInAndOut->Init() || !_pCoinNumInAndOut->Init() ||
		!_pTrustNumInAndOut->Init()) {
		return false;
	}

	MoveInit();

	if (!_pBarPinkBase->Init(40) || !_pBarRedBase->Init(_pPlayerInfo->GetMentalNum())) {
		return false;
	}

	if (!_pCoinNum->Init(6) || !_pTrustNum->Init(2)) {
		return false;
	}

	auto onSelect = [this]() {
		//�T�E���h�炷
		_pSoundManager->PlaySECommon(SoundManager::SECommon::Select);
	};

	_pCancelSelectBase->SetOnSelect(onSelect);
	_pSettingSelectBase->SetOnSelect(onSelect);
	_pBstorySelectBase->SetOnSelect(onSelect);
	_pBitemSelectBase->SetOnSelect(onSelect);

    return true;
}

void UIRoomMenu::Process() {

	MoveProcess();

	_end = false;
	_start = false;

	//�v�Z�̃v���O����

	int molecule = _pPlayerInfo->GetMolecule();
	int favor = _pPlayerInfo->GetFavor();

	if (!_pBarPinkBase->IsStart()) {
		if (_pBarPinkBase->GetNowRate() != molecule) {
			if (_lastMolecule != molecule) {  //�����O�̒l�ƍ����Ⴄ�Ȃ�
			

				//�O�̍D���x�̍��v - ���̍D���x�̍��v 
				_lastMolecule - molecule;

				_pBarPinkBase->SetLoopNum(0);  //SetLoop(����Max�ɓ��B�����邩)
				_pBarPinkBase->SetRate(molecule);  //pink���x���A�b�v�Q�[�W
			}
		}
	}
	_pTrustNum->SetNum(_pPlayerInfo->GetFavor());  //�D���x����

	if (_pPlayerInfo->GetMentalNum() != _lastMentalNum) {
		if (_pPlayerInfo->GetMentalNum() > _lastMentalNum ) {
			//up���x���t���[���݂���
			if (_lastMentalNum != 0) {
				_pSoundManager->PlaySECommon(SoundManager::SECommon::BarUp,200);
			}
		}
		else {
			//down���x���t���[���݂���
			_pSoundManager->PlaySECommon(SoundManager::SECommon::BarDown,200);
		}
		_pBarRedBase->SetRate(_pPlayerInfo->GetMentalNum());  //1�񂾂�
	}

	_pCoinNum->SetNum(_pPlayerInfo->GetCoin());  //�R�C������
	
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

	_pSoundManager->Process();

	_lastMentalNum = _pPlayerInfo->GetMentalNum();
	_lastMolecule = molecule;
}

void UIRoomMenu::Draw() {

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

	DrawFormatString(20, 950, GetColor(255, 205, 0), "GameMenu����:%d", _pPlayerInfo->GetFavor());
	DrawFormatString(20, 970, GetColor(255, 205, 0), "GameMenu���q:%d", _pPlayerInfo->GetMolecule());
	DrawFormatString(20, 1000, GetColor(255, 205, 0), "GameMenubar:%d", _pPlayerInfo->GetMentalNum());
}

//================================================
bool UIRoomMenu::DrawInit() {

	//�~�{�^�� ����180

	int handle = ResourceServer::LoadGraph("png/RoomUI/closeButton.png");
	int handle2 = ResourceServer::LoadGraph("png/RoomUI/closeButton_select.png");

	if (handle == -1 && handle2 == -1) {
		return false;
	}

	DrawInfo info = { handle,1870,10,true,1980,10 };
	DrawInfo info2 = { handle2,1870,10,true ,1980,10 };

	_pCancelSelectBase->SetDrawInfo(info);
	_pCancelSelectBase->SetDrawInfo(info2);

	//========================================================================
	//�ݒ�A�C�R��

	handle = ResourceServer::LoadGraph("png/RoomUI/setting.png");
	handle2 = ResourceServer::LoadGraph("png/RoomUI/setting_select.png");

	if (handle == -1 && handle2 == -1) {
		return false;
	}

	info = { handle,1800,20,true,1980,20 };
	info2 = { handle2,1800,20,true ,1980,20 };

	_pSettingSelectBase->SetDrawInfo(info);
	_pSettingSelectBase->SetDrawInfo(info2);

	//=========================================================================
	//�X�g�[���[�{�^��

	handle = ResourceServer::LoadGraph("png/RoomUI/button_story_brack.png");
	handle2 = ResourceServer::LoadGraph("png/RoomUI/button_story_white.png");

	if (handle == -1 && handle2 == -1) {
		return false;
	}

	info = { handle,1625,30,true,1980,30 };
	info2 = { handle2,1625,30,true ,1980,30 };

	_pBstorySelectBase->SetDrawInfo(info);
	_pBstorySelectBase->SetDrawInfo(info2);

	//=========================================================================
	//�A�C�e���{�^��

	handle = ResourceServer::LoadGraph("png/RoomUI/button_item_black.png");
	handle2 = ResourceServer::LoadGraph("png/RoomUI/button_item_white.png");

	if (handle == -1 && handle2 == -1) {
		return false;
	}

	info = { handle,1450,30,true,1980,30 };
	info2 = { handle2,1450,30,true ,1980,30 };

	_pBitemSelectBase->SetDrawInfo(info);
	_pBitemSelectBase->SetDrawInfo(info2);

	//==========================================================================
	//�̗̓Q�[�WPink 700*50

	handle = ResourceServer::LoadGraph("png/RoomUI/bar_base.png");
	handle2 = ResourceServer::LoadGraph("png/RoomUI/bar_pink.png");
	

	if (handle == -1 && handle2 == -1) {
		return false;
	}

	info = { handle,200,46,true,-760,46 };
	info2 = { handle2,200,46,true ,-760,46 };

	_pBarPinkBase->SetDrawInfo(info);
	_pBarPinkBase->SetDrawInfo(info2);


	//===========================================================================
	//�̗̓Q�[�WRed  600*40

	handle = ResourceServer::LoadGraph("png/RoomUI/bar_base_2.png");
	handle2 = ResourceServer::LoadGraph("png/RoomUI/bar_red.png");

	if (handle == -1 && handle2 == -1) {
		return false;
	}

	info = { handle,160,137,true,-660,137 };
	info2 = { handle2,160,137,true ,-660,137 };

	_pBarRedBase->SetDrawInfo(info);
	_pBarRedBase->SetDrawInfo(info2);

	//=============================================================
	//�T�[�N�� 430*430
	handle = ResourceServer::LoadGraph("png/RoomUI/uiCircle.png");

	if (handle == -1) {
		return false;
	}

	info = { handle,-136,-150,true,-430,-430 };

	_pCircleBase->SetDrawInfo(info);

	//==========================================================
	//CoinBase 215*52
	handle = ResourceServer::LoadGraph("png/RoomUI/number/coinBase.png");

	if (handle == -1) {
		return false;
	}

	info = { handle,10,10,true,-430,-430 };

	_pCoinBaseBase->SetDrawInfo(info);

	//======================================================
	//CoinNum
	std::array<int, 10> coinHandle{
		ResourceServer::LoadGraph("png/RoomUI/number/coin0.png"),
		ResourceServer::LoadGraph("png/RoomUI/number/coin1.png"),
		ResourceServer::LoadGraph("png/RoomUI/number/coin2.png"),
		ResourceServer::LoadGraph("png/RoomUI/number/coin3.png"),
		ResourceServer::LoadGraph("png/RoomUI/number/coin4.png"),
		ResourceServer::LoadGraph("png/RoomUI/number/coin5.png"),
		ResourceServer::LoadGraph("png/RoomUI/number/coin6.png"),
		ResourceServer::LoadGraph("png/RoomUI/number/coin7.png"),
		ResourceServer::LoadGraph("png/RoomUI/number/coin8.png"),
		ResourceServer::LoadGraph("png/RoomUI/number/coin9.png"),
	};

	//coin�̈ʒu��Draw��Set����

	for (int i = 0; i < 10; i++) {
		info = { coinHandle[i] ,175,18,true,-430,-430 };

		_pCoinNum->SetDrawInfo(info);
	}
	_pCoinNum->SetPoint({ 175,18 });

	//===============================================================
	//trustNum
	
	std::array<int, 10> trustHandle{
	ResourceServer::LoadGraph("png/RoomUI/number/trust0.png"),
	ResourceServer::LoadGraph("png/RoomUI/number/trust1.png"),
	ResourceServer::LoadGraph("png/RoomUI/number/trust2.png"),
	ResourceServer::LoadGraph("png/RoomUI/number/trust3.png"),
	ResourceServer::LoadGraph("png/RoomUI/number/trust4.png"),
	ResourceServer::LoadGraph("png/RoomUI/number/trust5.png"),
	ResourceServer::LoadGraph("png/RoomUI/number/trust6.png"),
	ResourceServer::LoadGraph("png/RoomUI/number/trust7.png"),
	ResourceServer::LoadGraph("png/RoomUI/number/trust8.png"),
	ResourceServer::LoadGraph("png/RoomUI/number/trust9.png"),
	};

	//�����̈ʒu��Set�ł���

	for (int i = 0; i < 10; i++) {
		info = { trustHandle[i] ,110,85,true,-430,-430 };

		_pTrustNum->SetDrawInfo(info);
	}
	_pTrustNum->SetPoint({ 110,85 });

	return true;
}

void UIRoomMenu::MoveInit() {

	//=====================================
	_pCancelSelectBase->SetRadius(20.0f);  //type���T�[�N���ɂ��Ă���

	DrawInfo infoInit;
	_pCancelSelectBase->GetDrawInfo(1, infoInit);

	_pCancelInAndOut->SetStartPosition(infoInit.startXY);
	_pCancelInAndOut->SetEndPosition(infoInit.xy);
	_pCancelInAndOut->SetNowPosition(infoInit.startXY);

	//=======================================
	//�ݒ�
	_pSettingSelectBase->SetRadius(50.0f);  //type���T�[�N���ɂ��Ă���

	_pSettingSelectBase->GetDrawInfo(0, infoInit);

	_pSettingInAndOut->SetStartPosition(infoInit.startXY);
	_pSettingInAndOut->SetEndPosition(infoInit.xy);
	_pSettingInAndOut->SetNowPosition(infoInit.startXY);

	//=======================================
	//�X�g�\��
	_pBstorySelectBase->SetRect();

	_pBstorySelectBase->GetDrawInfo(0, infoInit);

	_pBstoryInAndOut->SetStartPosition(infoInit.startXY);
	_pBstoryInAndOut->SetEndPosition(infoInit.xy);
	_pBstoryInAndOut->SetNowPosition(infoInit.startXY);
	 
	//=======================================
	//�A�C�e��
	_pBitemSelectBase->SetRect();

	_pBitemSelectBase->GetDrawInfo(0, infoInit);

	_pBitemInAndOut->SetStartPosition(infoInit.startXY);
	_pBitemInAndOut->SetEndPosition(infoInit.xy);
	_pBitemInAndOut->SetNowPosition(infoInit.startXY);

	//=============================================
	//(�����蔻�薳���̂�SetRadius���Ȃ��Ă悢)
	//�̗̓Q�[�W��
	_pBarPinkBase->GetDrawInfo(0, infoInit);

	_pBarPinkInAndOut->SetStartPosition(infoInit.startXY);
	_pBarPinkInAndOut->SetEndPosition(infoInit.xy);
	_pBarPinkInAndOut->SetNowPosition(infoInit.startXY);

	//===========================================
	//�̗̓Q�[�W��
	_pBarRedBase->GetDrawInfo(0, infoInit);

	_pBarRedInAndOut->SetStartPosition(infoInit.startXY);  //�������Z�b�g���Ȃ��Ƃ����Ȃ�
	_pBarRedInAndOut->SetEndPosition(infoInit.xy);
	_pBarRedInAndOut->SetNowPosition(infoInit.startXY);

	//=============================================
	//�T�[�N��
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

void UIRoomMenu::MoveProcess() {

	_cancel = _pCancelSelectBase->GetSelect();

	_pCancelSelectBase->SetPoint(0, _pCancelInAndOut->GetNowPosition());
	_pCancelSelectBase->SetPoint(1, _pCancelInAndOut->GetNowPosition());

	_pCancelInAndOut->SetIsEnd(_end);
	_pCancelInAndOut->SetIsStart(_start);

	_pCancelSelectBase->SetSelect(Utility::ImageHitDetection(_mouseX, _mouseY, _pCancelSelectBase.get()));

	//================================================
	//�ݒ�
	_setting = _pSettingSelectBase->GetSelect();

	_pSettingSelectBase->SetPoint(0, _pSettingInAndOut->GetNowPosition());
	_pSettingSelectBase->SetPoint(1, _pSettingInAndOut->GetNowPosition());

	_pSettingInAndOut->SetIsEnd(_end);
	_pSettingInAndOut->SetIsStart(_start);

	_pSettingSelectBase->SetSelect(Utility::ImageHitDetection(_mouseX, _mouseY, _pSettingSelectBase.get()));

	//================================================
	//�X�g�[���[
	_story = _pBstorySelectBase->GetSelect();

	_pBstorySelectBase->SetPoint(0, _pBstoryInAndOut->GetNowPosition());
	_pBstorySelectBase->SetPoint(1, _pBstoryInAndOut->GetNowPosition());

	_pBstoryInAndOut->SetIsEnd(_end);
	_pBstoryInAndOut->SetIsStart(_start);

	_pBstorySelectBase->SetSelect(Utility::ImageHitDetection(_mouseX, _mouseY, _pBstorySelectBase.get()));

	//===============================================
	//�A�C�e��
	_item = _pBitemSelectBase->GetSelect();

	_pBitemSelectBase->SetPoint(0, _pBitemInAndOut->GetNowPosition());
	_pBitemSelectBase->SetPoint(1, _pBitemInAndOut->GetNowPosition());

	_pBitemInAndOut->SetIsEnd(_end);
	_pBitemInAndOut->SetIsStart(_start);

	_pBitemSelectBase->SetSelect(Utility::ImageHitDetection(_mouseX, _mouseY, _pBitemSelectBase.get()));

	//===============================================
	//�̗�pink

	_pBarPinkBase->SetPoint(0, _pBarPinkInAndOut->GetNowPosition());
	_pBarPinkBase->SetPoint(1, _pBarPinkInAndOut->GetNowPosition());
	_pBarPinkInAndOut->SetIsEnd(_end);
	_pBarPinkInAndOut->SetIsStart(_start);

	//�̗�red
	_pBarRedBase->SetPoint(0, _pBarRedInAndOut->GetNowPosition());
	_pBarRedBase->SetPoint(1, _pBarRedInAndOut->GetNowPosition());
	_pBarRedInAndOut->SetIsEnd(_end);
	_pBarRedInAndOut->SetIsStart(_start);

	//===============================================
	//�T�[�N��

	_pCircleBase->SetPoint(0, _pCircleInAndOut->GetNowPosition());


	/*
	��]�̏���
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