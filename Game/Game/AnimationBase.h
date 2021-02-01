#pragma once

#include <unordered_map>
#include "Model.h"

class AnimationBase : public Model {
public:
	AnimationBase();
	virtual ~AnimationBase();

	bool Load(const TCHAR* fileName,bool multiple = false) override;
	void Process() override;

	bool Play(bool loop, int index, float speed, int blendFrame = 0);
	void Stop();

	bool Attach(int index);
	bool Detach(int index);

	float GetTime(int index);

	void SetAnimationSpeed(float speed) {
		_animationSpeed = speed;
	}

	float GetAnimationSpeed() const {
		return _animationSpeed;
	}

protected:
	bool ImmediatePlay(int index);

	int _animationNum;
	int _playIndex;
	float _playTime;

	int _blendIndex;
	int _blendFrame;
	int _blendCount;
	float _blendTime;

	float _animationSpeed;
	bool _animationLoop;

	std::unordered_map<int, float> _mapAnimationTime;
};
