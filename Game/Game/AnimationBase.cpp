#include "AnimationBase.h"

namespace {
	constexpr float DEFAULT_ANIMATION_SPEED = 1.0f;
}

AnimationBase::AnimationBase() {

	_animationNum = -1;
	_playIndex = -1;
	_playTime = 0.0f;

	_blendIndex = -1;
	_blendFrame = 0;
	_blendCount = 0;
	_blendTime = 0.0f;

	_animationSpeed = DEFAULT_ANIMATION_SPEED;
	_animationLoop = false;
}

AnimationBase::~AnimationBase() {
}

bool AnimationBase::Load(const TCHAR* fileName, bool multiple) {

	if (!Model::Load(fileName)) {
		return false;
	}

	_animationNum = MV1GetAnimNum(_handle);

	if (_animationNum == -1) {
		return false;
	}



	for (int i = 0; i < _animationNum; i++) {
		_mapAnimationTime.emplace(i, MV1GetAnimTotalTime(_handle, i));
	}

	return _animationNum != -1;
}

void AnimationBase::Process() {

	Model::Process();

	if (_playIndex >= 0) {
		
		if (_blendIndex >= 0 && _blendFrame > 0) {
			float rate = static_cast<float>(_blendCount) / static_cast<float>(_blendFrame);

			MV1SetAttachAnimBlendRate(_handle, _playIndex, 1.0f - rate);
			MV1SetAttachAnimBlendRate(_handle, _blendIndex, rate);

			if (_blendCount > _blendFrame) {
				// ブレンド前のアニメーションをデタッチ
				Detach(_playIndex);

				// ブレンドしていたアニメーションに切り替える
				_playIndex = _blendIndex;
				_playTime = _blendTime;

				_blendIndex = -1;
				_blendFrame = 0;
				_blendCount = 0;
				_blendTime = 0.0f;
			}
			else {
				_blendCount++;

				MV1SetAttachAnimTime(_handle, _blendIndex, _blendTime);

				_blendTime += _animationSpeed;

				float totalTime = _mapAnimationTime[_blendIndex];

				if (_blendTime > totalTime) {
					_blendTime = _animationLoop ? 0.0f : totalTime;
				}
			}
		}

		MV1SetAttachAnimTime(_handle, _playIndex, _playTime);

		_playTime += _animationSpeed;

		float totalTime = _mapAnimationTime[_playIndex];

		if (_playTime > totalTime) {
			_playTime = _animationLoop ? 0.0f : totalTime;
		}
	}
}

bool AnimationBase::Play(bool loop, int index, float speed, int blendFrame) {

	if (_animationNum == -1 || index < 0 || speed <= 0.0f || blendFrame < 0) {
		return false;
	}

	// 同じインデックスかブレント中は処理しない
	if (_playIndex == index || _blendIndex >= 0) {
		return false;
	}

	_animationLoop = loop;
	_animationSpeed = speed;

	if (_playIndex < 0) { // 現在再生しているアニメーションが無い

		return ImmediatePlay(index);
	}
	else { // 再生中のアニメーションがある

		if (blendFrame == 0) { // ブレンドフレーム指定が 0 なら即時切り替え

			Detach(_playIndex);

			return ImmediatePlay(index);
		}
		else { // ブレンドフレーム指定がある

			if (!Attach(index)) {
				return false;
			}

			_blendIndex = index;
			_blendFrame = blendFrame;
			_blendCount = 0;

			return true;
		}
	}
}

// アタッチ後に即再生
bool AnimationBase::ImmediatePlay(int index) {

	if (!Attach(index)) {
		return false;
	}

	_playIndex = index;

	return MV1SetAttachAnimTime(_handle, index, GetTime(index)) != -1;
}

void AnimationBase::Stop() {

	if (_playIndex >= 0) {

		Detach(_playIndex);

		_playIndex = -1;
	}

	if (_blendIndex >= 0) {

		Detach(_blendIndex);

		_blendIndex = -1;
		_blendFrame = 0;
		_blendCount = 0;
	}
}

bool AnimationBase::Attach(int index) {

	if (_animationNum == -1) {
		return false;
	}

	if (MV1AttachAnim(_handle, index, -1, FALSE) == -1) {
		return false;
	}

	return true;
}

bool AnimationBase::Detach(int index) {

	if (_animationNum == -1) {
		return false;
	}

	return MV1DetachAnim(_handle, index) != -1;
}

float AnimationBase::GetTime(int index) {

	auto count = _mapAnimationTime.count(index);

	if (count == 0) {
		return 0.0f;
	}

	return _mapAnimationTime[index];
}