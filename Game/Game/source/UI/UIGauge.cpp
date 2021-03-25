#include "UIGauge.h"
#include <cmath>
#include "Dxlib.h"

UIGauge::UIGauge() :UI2DBase(){

    _pTween = nullptr;

	_point = { 0,0 };
	_leftUp = { 0,0 };
	_rightDown = { 0,0 };

	_imageWidth = 0;
	_imageHeight = 0;

	_tweenFrame = 30;

	_rate = {0,0};
	_lastRate = {0,0};
}

UIGauge::~UIGauge() {
}

bool UIGauge::Init(int frame) {
	if (GetGraphSize(_vDrawInfo[1].handle, &_imageWidth, &_imageHeight) == -1) {
		return false;
	}

	_tweenFrame = frame;

	_pTween.reset(new Tween);

	_point = UI2DBase::GetPoint();


	_rightDown = _point;

	//_rightDown.x += _imageWidth;  //Max
	_rightDown.y += _imageHeight;

	return true;
}

void UIGauge::Process() {

	if (_pTween == nullptr) {
		return;
	}

	_point = UI2DBase::GetPoint();

	if (_pTween->IsStart()) {
		GaugeTween();
	}

	if (_pTween->IsEnd()) {
		GaugeTween();
		_lastRate = _rate;
	}

	_pTween->Process();
}

void UIGauge::GaugeTween() {

	float rate = static_cast<float>(_rate.x) / 100.0f;  //既に0.5
	int width = static_cast<int>(_imageWidth * rate);

	_rightDown.x = _point.x + width;
}

void UIGauge::Draw() {

	DrawGraph(_point.x, _point.y, UI2DBase::_vDrawInfo[0].handle, TRUE);
	SetDrawArea(_point.x, _point.y, _rightDown.x, _rightDown.y);
	DrawGraph(_point.x, _point.y, UI2DBase::_vDrawInfo[1].handle, TRUE);
	SetDrawArea(0, 0,1920, 1080);  //描画範囲を戻す　　これがバグの原因で赤に影響が出てる
}

bool UIGauge::SetRate(int rate) {

	if (_pTween == nullptr || rate < 0 || rate > 100) {
		return false;
	}

	_lastRate.x = _rate.x;
	_rate.x = rate;

	//Point start = { _lastRate.x ,0 };
	//Point end = { _rate.x,0 };

	_pTween->SetTween(_lastRate, _rate, _tweenFrame, Tween::Type::SineEnd);

	return true;
}