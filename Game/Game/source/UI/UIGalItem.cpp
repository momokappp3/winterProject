#include "UIGalItem.h"
#include "../../ResourceServer.h"
#include "../../Utility.h"

UIGalItem::UIGalItem() {

	//_pTween = nullptr;

	_pBackImageBase = nullptr;
	_pMoneyBSelectBase = nullptr;
	_pTequilaBSelectBase = nullptr;

	_moneyString = { _T("�������Z�Z�~�n��"),1270,430,false };
	_tequilaString = { _T("�e�L�[����n��\n�D���x�̏㏸�ɕω���!?"),1270,432,false };
}

UIGalItem::~UIGalItem() {
}

bool UIGalItem::Init() {

	_pBackImageBase.reset(new UI2DBase);
	_pMoneyBSelectBase.reset(new UI2DSelectBase);
	_pTequilaBSelectBase.reset(new UI2DSelectBase);

	//_pTween.reset(new Tween);

	//�R�}���hvector�Ɏg��������false��pushBack
	_vComandSelect.push_back(false);
	_vComandSelect.push_back(false);

	_closePoint = { 1112,100 };
	UIUseBase::Init();

	int handle = ResourceServer::LoadGraph("png/galUI/use/useItemBase.png");

	if (handle == -1) {
		return false;
	}

	DrawInfo info = { handle,1100,95,true };
	_pBackImageBase->SetDrawInfo(info);

	//====================================================================
	//�����A�C�e���{�^��
	handle = ResourceServer::LoadGraph("png/galUI/use/moneyBItem.png");
	int handle2 = ResourceServer::LoadGraph("png/galUI/use/moneyBItemSelect.png");

	if (handle == -1 && handle2 == -1) {
		return false;
	}

	info = { handle,1160,130,true };
	DrawInfo info2 = { handle2,1160,130,true };

	_pMoneyBSelectBase->SetDrawInfo(info);
	_pMoneyBSelectBase->SetDrawInfo(info2);

	_pMoneyBSelectBase->SetRect();

	//=============================================================
	//�e�L�[���A�C�e���{�^��
	handle = ResourceServer::LoadGraph("png/galUI/use/useBTequila.png");
	handle2 = ResourceServer::LoadGraph("png/galUI/use/useBTequilaSelect.png");

	if (handle == -1 && handle2 == -1) {
		return false;
	}

	info = { handle,1380,130,true };
	info2 = { handle2,1380,130,true };

	_pTequilaBSelectBase->SetDrawInfo(info);
	_pTequilaBSelectBase->SetDrawInfo(info2);

	_pTequilaBSelectBase->SetRect();

	return true;
}

void UIGalItem::Process() {

	UIUseBase::Process();

	_vComandSelect[0] = _pMoneyBSelectBase->GetSelect();
	_pMoneyBSelectBase->SetSelect(Utility::ImageHitDetection(_mouseX, _mouseY, _pMoneyBSelectBase.get()));

	_vComandSelect[1] = _pTequilaBSelectBase->GetSelect();
	_pTequilaBSelectBase->SetSelect(Utility::ImageHitDetection(_mouseX, _mouseY, _pTequilaBSelectBase.get()));

	_pBackImageBase->Process();
	_pMoneyBSelectBase->Process();
	_pTequilaBSelectBase->Process();

	UIUseBase::Process();
}

void UIGalItem::Draw() {

	if (_nowMode) {
		_pBackImageBase->Draw();
		_pMoneyBSelectBase->Draw();
		_pTequilaBSelectBase->Draw();
		UIUseBase::Draw();

	}
}