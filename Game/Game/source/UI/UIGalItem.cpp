#include "UIGalItem.h"
#include "../../ResourceServer.h"
#include "../../Utility.h"

UIGalItem::UIGalItem() {

	//_pTween = nullptr;

	_pBackImageBase = nullptr;
	_pMoneyBSelectBase = nullptr;
	_pTequilaBSelectBase = nullptr;

	_pUIPopUp = nullptr;

	_vString.clear();

}

UIGalItem::~UIGalItem() {
}

bool UIGalItem::Init() {

	_pBackImageBase.reset(new UI2DBase);
	_pMoneyBSelectBase.reset(new UI2DSelectBase);
	_pTequilaBSelectBase.reset(new UI2DSelectBase);

	_pUIPopUp.reset(new UIPopUp);

	if (!_pUIPopUp->Init()) {
		return false;
	}

	//_pTween.reset(new Tween);

	//コマンドvectorに使う分だけfalseをpushBack
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
	//お金アイテムボタン
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
	//テキーラアイテムボタン
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


	if (!_pUIPopUp->GetNowMode()) {
		_vComandSelect[0] = _pMoneyBSelectBase->GetSelect();
		_pMoneyBSelectBase->SetSelect(Utility::ImageHitDetection(_mouseX, _mouseY, _pMoneyBSelectBase.get()));

		_vComandSelect[1] = _pTequilaBSelectBase->GetSelect();
		_pTequilaBSelectBase->SetSelect(Utility::ImageHitDetection(_mouseX, _mouseY, _pTequilaBSelectBase.get()));
	}

	for (int i = 0; i < _vComandSelect.size(); i++) {
		if (_vComandSelect[i] && _mouseLeft) {
			_pUIPopUp->SetNowMode(true);
			break;
		}
	}

	if (_pUIPopUp->GetNowMode()) {
		_closeUse = false;
	}
	if (!_pUIPopUp->GetNowMode()) {
		_closeUse = true;
	}

	_pBackImageBase->Process();
	_pMoneyBSelectBase->Process();
	_pTequilaBSelectBase->Process();
	_pUIPopUp->Process();
	_pUIPopUp->SetMouse(_mouseX, _mouseY);
	_pUIPopUp->SetLeft(_mouseLeft);

	UIUseBase::Process();
}

void UIGalItem::Draw() {

	if (_nowMode) {
		_pBackImageBase->Draw();
		_pMoneyBSelectBase->Draw();
		_pTequilaBSelectBase->Draw();
		UIUseBase::Draw();

		if (_pUIPopUp->GetNowMode()) {
			_pUIPopUp->Draw();
			if (_pUIPopUp->GetClose()&& _mouseLeft || _pUIPopUp->GetOk() && _mouseLeft) {
				_pUIPopUp->SetNowMode(false);
			}
		}
	}
}