#pragma once
#include "UI2DBase.h"
#include "../../../../AppFrame/Tween.h"
#include <memory>

/*
_vDrawInfo[0] ��Base��
_vDrawInfo[1] �ɃQ�[�W��

*/

class UIGauge :public UI2DBase{
public:
    UIGauge();
    virtual ~UIGauge();

	bool Init(int frame);
    void Process()override;
    void Draw() override;

	bool SetRate(int rate);  //������Ă΂Ȃ��ƃo�O�̉\������

	bool IsStart() {
		if (_pTween == nullptr){
			return false;
		}

		return _pTween->IsStart();
	}
	
	int GetNowRate(){
		return _rate;
	}
	

private:

	void GetGaugeArea();

	std::unique_ptr<Tween> _pTween;

	Point _point;  //������DrawInfo��
	Point _leftUp;  //�`��\�̈��������`�̍���̒��_
	Point _rightDown;  //�`��\�̈��������`�̉E���{�P�̒�

	int _imageWidth;
	int _imageHeight;

	int _tweenFrame;

	int _lastRate;
	int _rate;
	int _nowRate;

};
