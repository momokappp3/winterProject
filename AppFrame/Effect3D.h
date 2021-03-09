#pragma once
#include <tchar.h>
#include "Types.h"
#include "../AppFrame/source/Mode/ModeBase.h"

class Effect3D : public ModeBase {
public:
	Effect3D();
	virtual ~Effect3D();

	/*
	bool Init(const TCHAR* fileName, float magnification, bool isLoop);
	virtual void Start();
	virtual void Stop();
	virtual void Process();
	virtual void ProcessPoint();
	virtual void Delete();
	virtual void Draw();

	Point GetPoint() {
		return _point;
	}

	void SetPoint(Point point) {
		_point = point;
	}

protected:

	Point _point;

	int _effectResourceHandle;
	int _playingEffectHandle;   //���������Ɏg��

	bool _isLoop;
	bool _isEnd;

	*/

	virtual bool Init(const TCHAR* fileName, float magnification);
	virtual bool Terminate();
	virtual bool Process();
	virtual void Draw();

protected:
	int		_effectResourceHandle;		// �G�t�F�N�g�t�@�C�������[�h����n���h��
	int		_playingEffectHandle;		// ���[�h�����G�t�F�N�g�t�@�C������A�G�t�F�N�g�𐶐���������

	// �G�t�F�N�g�ʒu
	float	_position_x = 0.0f;
	float	_position_y = 0.0f;
};