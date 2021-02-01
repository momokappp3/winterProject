#pragma once
#include "AnimationBase.h"

class AnimationOtoko : public AnimationBase {
public:
	AnimationOtoko();
	virtual ~AnimationOtoko();

	enum class STATUS {
		NONE,
		WAIT,
		WALK,
		_EOT_
	};







};