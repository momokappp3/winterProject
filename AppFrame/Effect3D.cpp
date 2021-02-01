#include "Effect3D.h"
#include "EffekseerForDXLib.h"


Effect3D::Effect3D() {

	_point = { 0,-150 };

	_effectResourceHandle = -1;
	_playingEffectHandle = -1;

	_isLoop = false;
	_isEnd = false;
}

Effect3D::~Effect3D() {
}


//�n���h���Ɗg�嗦���Z�b�g
bool Effect3D::Init(const TCHAR* fileName, float magnification, bool isLoop) {

	_effectResourceHandle = LoadEffekseerEffect(fileName, magnification);

	if (_effectResourceHandle == -1) {
		return false;
	}

	_isLoop = isLoop;

	return true;
}

void Effect3D::Start() {

	if (_effectResourceHandle == -1) {
		return;
	}

	// �G�t�F�N�g���Đ�����B
	_playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);
	DrawEffekseer3D_Begin();

}

void Effect3D::Stop() {

	if (_playingEffectHandle == -1) {
		return;
	}

	StopEffekseer3DEffect(_playingEffectHandle);
	DrawEffekseer3D_End();

	_playingEffectHandle = -1;
}

void Effect3D::Process() {

	if (_playingEffectHandle == -1) {
		return;
	}

	// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����B
	Effekseer_Sync3DSetting();

	ProcessPoint();

	// �Đ����̃G�t�F�N�g���ړ�����B
	SetPosPlayingEffekseer3DEffect(_playingEffectHandle, _point.x, _point.y, 0);

	if (_isLoop) {
		//�Đ�����
		if (IsEffekseer3DEffectPlaying(_playingEffectHandle) == -1) {
			_playingEffectHandle = PlayEffekseer3DEffect(_effectResourceHandle);
			DrawEffekseer3D_Begin();
		}
	}
	else {
		StopEffekseer3DEffect(_playingEffectHandle);
		DrawEffekseer3D_End();
		// 3D��\������B
		DrawCapsule3D(
			VGet(0.0f, 100.0f, 0.0f), VGet(0.0f, -100.0f, 0.0f), 6.0f, 16, GetColor(100, 100, 100), GetColor(255, 255, 255), TRUE);
	}

}

void Effect3D::ProcessPoint() {
}

void Effect3D::Delete() {

	Stop();

	if (_effectResourceHandle != -1) {
		DeleteEffekseerEffect(_effectResourceHandle);
	}
}