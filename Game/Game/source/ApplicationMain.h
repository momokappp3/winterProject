#pragma once
#include "appframe.h"
#include "../AnimationBase.h"

class ApplicationMain : public ApplicationBase {
public:
	bool Initialize(HINSTANCE hInstance) override;
	bool Terminate() override;
	bool Input() override;
	bool Process() override;
	bool Render() override;

	bool AppWindowed() override {
#ifdef _DEBUG  //デバッグビルド
		return true; 
#else   //リリースビルド
		return false;
#endif
	}
	/*
	int DispSizeW() override { return 1920; }
	int DispSizeH() override { return 1080; }
	*/
protected:
}; 
