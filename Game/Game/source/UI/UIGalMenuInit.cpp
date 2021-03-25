#include "UIGalMenuInit.h"
#include "../../ResourceServer.h"
#include "../../Utility.h"

UIGalMenuInit::UIGalMenuInit(){

	_ModeType = GalGameUIType::Max;

	_pMenuSelectBase = nullptr;
	_pMenuInAndOut = nullptr;

	_start = false;
	_end = false;

	_mouseX = -1;
	_mouseY = -1;

	_num = 0;
}

UIGalMenuInit::~UIGalMenuInit() {
}

bool UIGalMenuInit::Init() {

	_ModeType = GalGameUIType::MenuIinit;

	_pMenuSelectBase.reset(new UI2DSelectBase);
	_pMenuInAndOut.reset(new UIInAndOut);

	_pMenuInAndOut->Init();

	int handle = ResourceServer::LoadGraph("png/galUI/menu.png");
	int handle2 = ResourceServer::LoadGraph("png/galUI/menu_select.png");


	if (handle == -1 && handle2 == -1) { 
		return false;
	}

	DrawInfo info = { handle,1800,20,true,1980,20 };
	DrawInfo info2 = { handle2,1800,20,true ,1980,20 };

	_pMenuSelectBase->SetDrawInfo(info);
	_pMenuSelectBase->SetDrawInfo(info2);

	//================================================
	//InAndOut動きの処理

	_pMenuSelectBase->SetRadius(50.0f);  //typeをサークルにしている

	DrawInfo infoInit;
	_pMenuSelectBase->GetDrawInfo(1,infoInit);

	_pMenuInAndOut->SetStartPosition(infoInit.startXY);
	_pMenuInAndOut->SetEndPosition(infoInit.xy);
	_pMenuInAndOut->SetNowPosition(infoInit.xy);

	return true;
}

void UIGalMenuInit::Process() {

	_select = _pMenuSelectBase->GetSelect();

	_pMenuSelectBase->SetPoint(0,_pMenuInAndOut->GetNowPosition());
	_pMenuSelectBase->SetPoint(1, _pMenuInAndOut->GetNowPosition());

	_pMenuInAndOut->SetIsEnd(_end);
	_pMenuInAndOut->SetIsStart(_start);

	_end = false;
	_start = false;

	//_pMenuSelectBase.get() スマートポインタから普通のポインタに
	_pMenuSelectBase->SetSelect(Utility::ImageHitDetection(_mouseX, _mouseY, _pMenuSelectBase.get()));

	_pMenuInAndOut->Process();
	_pMenuSelectBase->Process();

}

void UIGalMenuInit::Draw() {

	_pMenuSelectBase->Draw();
}