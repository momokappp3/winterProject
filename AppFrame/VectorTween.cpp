#include "VectorTween.h"
#include <cmath>

namespace {

	const float pi = std::acosf(-1);

	float DegreeToRadian(float degree) {   //度からラジアンに変える関数
		return degree * pi / 180.0f;
	}
}

VectorTween::VectorTween() {

	_start = { 0,0,0 };
	_end = { 0,0,0 };
	_position = { 0,0,0 };

	_type = Type::Linear;
	_timer = 0;
	_frame = 0;

	_rate = 0.0f;

	_isStart = false;
	_isEnd = false;
}

VectorTween::~VectorTween() {
}

bool VectorTween::SetVectorTween(VECTOR start, VECTOR end, int flame, Type type) {
	
	_isStart = false; //バグったので追加

	if (_isStart) {  //ここで2回目がバグる
		return false;
	}
	_isStart = true;
	_isEnd = false;
	_start = start;
	_end = end;
	_timer = 0;
	_frame = flame;
	_type = type;
	_position = start;

	return true;
}

void VectorTween::Process() {

	if (!_isStart || _isEnd) {   //スタートしていてエンドになっていない
		return;
	}

	if (_timer == _frame) {
		_isEnd = true;
		_rate = 1.0f;
		_position = _end;
		return;
	}

	VECTOR base = { _end.x - _start.x,_end.y - _start.y, _end.z - _start.z};
	float rate = static_cast<float>(_timer) / static_cast<float>(_frame);
	float x = 0.0f, y = 0.0f, z = 0.0f, radian = 0.0f, sineRate = 0.0f, radianBase = 0.0f;

	_rate = rate;

	switch (_type) {
	case Type::Linear:
		break;

	case Type::SineStart:
		radian = DegreeToRadian(90.0f);
		sineRate = std::sin(radian * rate);

		rate = sineRate;
		break;

	case Type::SineEnd:
		radianBase = DegreeToRadian(270.0f);
		radian = DegreeToRadian(90.0f);
		sineRate = std::sin(radianBase + radian * rate) + 1.0f;   //sinの270°から360°は-1から0を返すので+1して0から1に変換する

		rate = sineRate;
		break;

	default:
		break;
	}

	x = base.x * rate;
	y = base.y * rate;
	z = base.z * rate;

	_position = { _start.x + x, _start.y + y, _start.z + z };
	_timer++;
}