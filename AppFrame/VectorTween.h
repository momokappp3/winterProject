#pragma once
#include "Dxlib.h"
#include "Types.h"

class VectorTween {
public:
	VectorTween();
	virtual ~VectorTween();

	enum class Type {
		Linear = 0,   //íºê¸
		SineStart,
		SineEnd,
		Max,
	};

	bool SetVectorTween(VECTOR start, VECTOR end, int flame, Type type = Type::Linear);
	void Process();
	void Reset() {
		_isStart = false;
		_isEnd = false;
	}

	bool IsStart() {
		return _isStart;
	}
	bool IsEnd() {
		return _isEnd;
	}
	VECTOR GetPosition() {
		return _position;
	}

	float GetRate() {
		return _rate;
	}

private:

	VECTOR _start;
	VECTOR _end;
	VECTOR _position;

	Type _type;
	int _frame;
	int _timer;

	float _rate;

	bool _isStart;
	bool _isEnd;
};