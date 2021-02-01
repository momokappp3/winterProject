#pragma once

class MouseInput {
public:
	MouseInput();
	virtual ~MouseInput();

	void Process();
	void Draw();

	bool GetRight() {
		return _isRight;
	}

	bool GetLeft() {
		return _isLeft;
	}

private:

	bool _isRight;
	bool _isLeft;

	int _posX;
	int _posY;
};