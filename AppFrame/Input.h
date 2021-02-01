#pragma once

class Input {
public:
	Input();
	virtual ~Input();

	void Process();

	int _key[256];
	
};
