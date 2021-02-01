
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

	// 処理前のステータスを保存しておく
	STATUS oldStatus = _status;

	// ステータスが変わっていないか？
	if (oldStatus == _status) {
		// 再生時間を進める
		_playTime += 0.5f;
	}
	else {
		// アニメーションがアタッチされていたら、デタッチする
		if (_attachIndex != -1) {
			Detach();
		}
		// ステータスに合わせてアニメーションのアタッチ
		switch (_status) {
		case STATUS::WAIT:
			_attachIndex = Atachi(0);
			break;
		case STATUS::WALK:
			_attachIndex = Atachi(1);
			break;
		}
		// アタッチしたアニメーションの総再生時間を取得する
		_totalTime = MV1GetAttachAnimTotalTime(_handle, _attachIndex);
		// 再生時間を初期化
		_playTime = 0.0f;
	}

	// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
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