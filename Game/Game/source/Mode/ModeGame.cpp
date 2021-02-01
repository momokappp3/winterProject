/*

����
���f���\�������[�V����

�g�ݍ��킹�ĕ\�����[�V����OK

*/


#include "AppFrame.h"
#include "../ApplicationMain.h"
#include "../Mode/ModeGame.h"

bool ModeGame::Initialize() {

	if (!ModeBase::Initialize()) {
		return false; 
	}
	_pCamera = nullptr;
	_pEffect3D = nullptr;
	_pCamera.reset(new Camera);
	_pEffect3D.reset(new Effect3D);

	_cg = MV1LoadModel("model/otoko/otoko.pmx");
	_cg2 = MV1LoadModel("model/tue/tue.pmx");

	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���(�J�����̏����ʒu)
	//SetCameraNearFar(0.1f, 800.0f);

	//(0,10,-20)�̎��_����(0,10,0)�̃^�[�Q�b�g������p�x�ɃJ������ݒu
	//SetCameraPositionAndTarget_UpVecY(VGet(0, 10, -20), VGet(0.0f, 10.0f, 0.0f));

	//�J�����N���X�Ŏ���

	_pCamera->SetPosition(0.0f, 10.0f, -20.0f);
	_pCamera->SetTarget(0.0f, 10.0f, 0.0f);
	_pCamera->SetNearFar(0.1f, 800.0f);


	_pEffect3D->Init("effect/test.efk", 1.0f, false);
	_pEffect3D->SetPoint({ 100,250});


	_attachIndex = MV1AttachAnim(_cg, 1, -1, FALSE);
	_attachIndex2 = MV1AttachAnim(_cg2, 1, -1, FALSE);

	_totalTime = MV1GetAttachAnimTotalTime(_cg, _attachIndex);
	_totalTime2 = MV1GetAttachAnimTotalTime(_cg2, _attachIndex2);

	_playTime = 0.0f;
	_playTime2 = 0.0f;

	return true;
}

bool ModeGame::Process() {
	ModeBase::Process();

	int key = ApplicationMain::GetInstance()->GetKey();

	/*======================================
	�A�j��
	=======================================*/


	if (key & PAD_INPUT_A) {
		_x += 8;
		// �Đ����Ԃ�i�߂�
		_playTime += 0.5f;
		_playTime2 += 0.5f;

		// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
		if (_playTime >= _totalTime) {
			_playTime = 0.0f;
		}
		// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
		if (_playTime2 >= _totalTime2) {
			_playTime2 = 0.0f;
		}
		// �Đ����Ԃ��Z�b�g����
		MV1SetAttachAnimTime(_cg, _attachIndex, _playTime);
		// �Đ����Ԃ��Z�b�g����
		MV1SetAttachAnimTime(_cg2, _attachIndex2, _playTime2);
	}


	if (key & PAD_INPUT_U) {
		//�G�t�F�N�g�o��
		_pEffect3D->Start();

	}

	if (_pEffect3D != nullptr) {
		_pEffect3D->Process();
	}

	_pCamera->Process();

	return true;
}

bool ModeGame::Render() {
	ModeBase::Render();


	_pCamera->Render();

	MV1DrawModel(_cg);
	MV1DrawModel(_cg2);

	DrawFormatString(500, 500, GetColor(255, 0, 0),"%lf:%lf",_playTime,_totalTime );
	DrawFormatString(500, 700, GetColor(255, 0, 0), "%lf:%lf", _playTime2, _totalTime2);



	return true;
}

bool ModeGame::Terminate() {
	ModeBase::Terminate();
	return true;
}

