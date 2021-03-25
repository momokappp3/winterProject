#pragma once
#include "UI2DBase.h"
#include "../../../../AppFrame/Tween.h"
#include <memory>

/*
_vDrawInfo[0] にBaseを
_vDrawInfo[1] にゲージを

*/

class UIGauge :public UI2DBase{
public:
    UIGauge();
    virtual ~UIGauge();

	bool Init(int frame);
    void Process()override;
    void Draw() override;

	bool SetRate(int rate);  //これを呼ばないとバグの可能性あり

private:

	void GaugeTween();

	std::unique_ptr<Tween> _pTween;

	Point _point;  //ここはDrawInfoを
	Point _leftUp;  //描画可能領域を示す矩形の左上の頂点
	Point _rightDown;  //描画可能領域を示す矩形の右下＋１の頂

	int _imageWidth;
	int _imageHeight;

	int _tweenFrame;

	Point _rate;  //yは使わない
	Point _lastRate;  //yは使わない

};
