#include "UIGalStory.h"
#include "../../ResourceServer.h"
#include "../../Utility.h"

UIGalStory::UIGalStory() {

	_pBackImageBase = nullptr;

	_pStringImageBase0 = nullptr;
	_pStringImageBase1 = nullptr;
	_pStringImageBase2 = nullptr;
	_pStringImageBase3 = nullptr;
	_pStringImageBase4 = nullptr;


	_imageSize = -1;
	_lastImageSize = -1;

	_story0String = { _T("メインストーリー1"),1270,430,false };
	_story1String = { _T("未定"),1390,440,false };
	_story2String = { _T("未定"),1390,440,false };
	_story3String = { _T("未定"),1390,440,false };
	_story4String = { _T("未定"),1390,440,false };

	_typeString = -1;

}

UIGalStory::~UIGalStory() {
}

bool UIGalStory::Init() {

	_pBackImageBase.reset(new UI2DBase);

	_pStringImageBase0.reset(new UI2DSelectBase);
	_pStringImageBase1.reset(new UI2DSelectBase);
	_pStringImageBase2.reset(new UI2DSelectBase);
	_pStringImageBase3.reset(new UI2DSelectBase);
	_pStringImageBase4.reset(new UI2DSelectBase);
	
	//=================================================================

	_closePoint = { 1012,100 };
	UIUseBase::Init();

	int handle = ResourceServer::LoadGraph("png/galUI/use/useStoryBase.png");

	if (handle == -1) {
		return false;
	}

	DrawInfo info = { handle,1000,95,true };
	_pBackImageBase->SetDrawInfo(info);

	for (int i = 0; i < 5; i++) {
		_vComandSelect.push_back(false);
	}

	handle = ResourceServer::LoadGraph("png/galUI/use/useStringBase.png");
	int handle2 = ResourceServer::LoadGraph("png/galUI/use/useStringBaseSelect.png");

	if (handle == -1 && handle2 == -1) {
		return false;
	}

	info = { handle,1060,130,true };
	DrawInfo info2 = { handle2,1060,130,true };

	_pStringImageBase0->SetDrawInfo(info);
	_pStringImageBase0->SetDrawInfo(info2);

	_pStringImageBase0->SetRect();

	info.xy.y += 90;
	info2.xy.y += 90;

	_pStringImageBase1->SetDrawInfo(info);
	_pStringImageBase1->SetDrawInfo(info2);
	_pStringImageBase1->SetRect();

	info.xy.y += 90;
	info2.xy.y += 90;

	_pStringImageBase2->SetDrawInfo(info);
	_pStringImageBase2->SetDrawInfo(info2);
	_pStringImageBase2->SetRect();

	info.xy.y += 90;
	info2.xy.y += 90;

	_pStringImageBase3->SetDrawInfo(info);
	_pStringImageBase3->SetDrawInfo(info2);
	_pStringImageBase3->SetRect();

	info.xy.y += 90;
	info2.xy.y += 90;

	_pStringImageBase4->SetDrawInfo(info);
	_pStringImageBase4->SetDrawInfo(info2);
	_pStringImageBase4->SetRect();
	return true;
}

void UIGalStory::Process() {


	_vComandSelect[0] = _pStringImageBase0->GetSelect();
	_pStringImageBase0->SetSelect(Utility::ImageHitDetection(_mouseX, _mouseY, _pStringImageBase0.get()));

	_vComandSelect[1] = _pStringImageBase1->GetSelect();
	_pStringImageBase1->SetSelect(Utility::ImageHitDetection(_mouseX, _mouseY, _pStringImageBase1.get()));

	_vComandSelect[2] = _pStringImageBase2->GetSelect();
	_pStringImageBase2->SetSelect(Utility::ImageHitDetection(_mouseX, _mouseY, _pStringImageBase2.get()));

	_vComandSelect[3] = _pStringImageBase3->GetSelect();
	_pStringImageBase3->SetSelect(Utility::ImageHitDetection(_mouseX, _mouseY, _pStringImageBase3.get()));

	_vComandSelect[4] = _pStringImageBase4->GetSelect();
	_pStringImageBase4->SetSelect(Utility::ImageHitDetection(_mouseX, _mouseY, _pStringImageBase4.get()));

	UIUseBase::Process();
	_pBackImageBase->Process();

	_pStringImageBase0->Process();
	_pStringImageBase1->Process();
	_pStringImageBase2->Process();
	_pStringImageBase3->Process();
	_pStringImageBase4->Process();

}

void UIGalStory::Draw() {

	if (_nowMode) {
		_pBackImageBase->Draw();
		UIUseBase::Draw();

		_pStringImageBase0->Draw();
		_pStringImageBase1->Draw();
		_pStringImageBase2->Draw();
		_pStringImageBase3->Draw();
		_pStringImageBase4->Draw();

		DrawFormatString(1135,145, GetColor(0, 0, 0),"メインストーリ―１");
		DrawFormatString(1135, 234, GetColor(0, 0, 0), "未定");
		DrawFormatString(1135, 325, GetColor(0, 0, 0), "未定");
		DrawFormatString(1135, 416, GetColor(0, 0, 0), "未定");
		DrawFormatString(1135, 504, GetColor(0, 0, 0), "未定");
	}
}