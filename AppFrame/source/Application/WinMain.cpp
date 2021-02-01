#include "../appframe.h"
#include "../../Fade.h"

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow) {

	ApplicationBase *appBase = ApplicationBase::GetInstance();  //生ポインタ

	if (!appBase) {
		return 0;
	}

	if (!appBase->Initialize(hInstance)) {
		return 0;
	}

	if (!Fade::Init()) {
		return -1;
	}

	while (ProcessMessage() == 0){
	
		appBase->Input();
		appBase->Process();

		Fade::Process();

		ClearDrawScreen();		// 画面を初期化する
		appBase->Render();

		Fade::Draw();
		ScreenFlip();			// 裏画面の内容を表画面に反映させる
	}

	appBase->Terminate();

	return 0;
}
