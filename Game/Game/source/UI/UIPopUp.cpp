#include "UIPopUp.h"
#include "../../ResourceServer.h"
#include "../../Utility.h"

UIPopUp::UIPopUp() {

    _pPopUpBase = nullptr;
    _pOkBSelectBase = nullptr;
    _pCloselBBase = nullptr;

	_ok = -1;
	_close = -1;

	_mouse = { 0,0 };
	_mouseLeft = false;

	_nowMode = false;
}

UIPopUp::~UIPopUp() {
}

bool UIPopUp::Init() {

	_pPopUpBase.reset(new UI2DBase);
	_pOkBSelectBase.reset(new UI2DSelectBase);
	_pCloselBBase.reset(new UI2DSelectBase);

	//=================================================================
	//popupBase
	int handle = ResourceServer::LoadGraph("png/galUI/use/popUp.png");

	if (handle == -1) {
		return false;
	}

	DrawInfo info = { handle,1130,330,true };
	_pPopUpBase->SetDrawInfo(info);


	//====================================================================
	//OK{^
	handle = ResourceServer::LoadGraph("png/galUI/use/OkB.png");
	int handle2 = ResourceServer::LoadGraph("png/galUI/use/OkBSelect.png");

	if (handle == -1 && handle2 == -1) {
		return false;
	}

	info = { handle,1400,550,true };
	DrawInfo info2 = { handle2,1400,550,true };

	_pOkBSelectBase->SetDrawInfo(info);
	_pOkBSelectBase->SetDrawInfo(info2);

	_pOkBSelectBase->SetRect();

	//====================================================================
	//close

	handle = ResourceServer::LoadGraph("png/galUI/closeButton.png");
	handle2 = ResourceServer::LoadGraph("png/galUI/closeButton_select.png");

	if (handle == -1 && handle2 == -1) {
		return false;
	}

	info = { handle,1140,340,true };
	info2 = { handle2,1140,340,true };

	_pCloselBBase->SetDrawInfo(info);
	_pCloselBBase->SetDrawInfo(info2);

	_pCloselBBase->SetRect();
}

void UIPopUp::Process() {

	_ok = _pOkBSelectBase->GetSelect();
	_pOkBSelectBase->SetSelect(Utility::ImageHitDetection(_mouse.x, _mouse.y, _pOkBSelectBase.get()));

	_close = _pCloselBBase->GetSelect();
	_pCloselBBase->SetSelect(Utility::ImageHitDetection(_mouse.x, _mouse.y, _pCloselBBase.get()));

	_pPopUpBase->Process();
	_pOkBSelectBase->Process();
	_pCloselBBase->Process();
}

void UIPopUp::Draw() {
	_pPopUpBase->Draw();
	_pOkBSelectBase->Draw();
	_pCloselBBase->Draw();
}
