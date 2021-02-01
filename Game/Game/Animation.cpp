
#include "Animation.h"

Animation::Animation() {

	_status = STATUS::NONE;

	_attachIndex = -1;
	_handle = -1;

	_totalTime = 0.0f;
	_playTime = 0.0f;
}

Animation::~Animation() {
}

bool Animation::SetHandle(int handle) {
	_handle = handle;

	return true;
}

void Animation::Process() {

	if (!_handle) {
		return;
	}

	// �����O�̃X�e�[�^�X��ۑ����Ă���
	STATUS oldStatus = _status;

	// �X�e�[�^�X���ς���Ă��Ȃ����H
	if (oldStatus == _status) {
		// �Đ����Ԃ�i�߂�
		_playTime += 0.5f;
	}
	else {
		// �A�j���[�V�������A�^�b�`����Ă�����A�f�^�b�`����
		if (_attachIndex != -1) {
			Detach();
		}
		// �X�e�[�^�X�ɍ��킹�ăA�j���[�V�����̃A�^�b�`
		switch (_status) {
		case STATUS::WAIT:
			_attachIndex = Atachi(0);
			break;
		case STATUS::WALK:
			_attachIndex = Atachi(1);
			break;
		}
		// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
		_totalTime = MV1GetAttachAnimTotalTime(_handle, _attachIndex);
		// �Đ����Ԃ�������
		_playTime = 0.0f;
	}

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	if (_playTime >= _totalTime) {
		_playTime = 0.0f;
	}

	DrawFormatString(500, 200, GetColor(255, 0, 0), "%lf:%lf", _playTime, _totalTime);
}

void Animation::Detach() {
	MV1DetachAnim(_handle, _attachIndex);
	_attachIndex = -1;

}

int Animation::Atachi(int num) {

	return MV1AttachAnim(_handle, num, -1, FALSE);
}