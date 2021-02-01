#pragma once


#include "Model.h"

class Animation : public Model {

	Animation();
	virtual ~Animation();

	enum class STATUS {
		NONE,
		WAIT,
		WALK,
		_EOT_
	};

	bool SetHandle(int handle);
	void Process();
	void Detach();
	//ステータスに合わせてアタッチ
	int Atachi(int num);

private:
	STATUS _status;

	int _attachIndex;
	int _handle;

	float _totalTime;
	float _playTime;

};
