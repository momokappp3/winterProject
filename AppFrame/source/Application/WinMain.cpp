#include "../appframe.h"
#include "../../Fade.h"

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow) {

	ApplicationBase *appBase = ApplicationBase::GetInstance();  //���|�C���^

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

		ClearDrawScreen();		// ��ʂ�����������
		appBase->Render();

		Fade::Draw();
		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f������
	}

	appBase->Terminate();

	return 0;
}
