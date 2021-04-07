/*

モードの登録

*/
#include "AppFrame.h"
#include "ApplicationMain.h"
#include "../source/Mode/ModeTitle.h"
#include "Mode/GalGame.h"
//#include "../Action3DGame.h"

// 実体
ApplicationMain	g_oApplicationMain;

bool ApplicationMain::Initialize(HINSTANCE hInstance) {
	if (!ApplicationBase::Initialize(hInstance)) { return false; }

	// 最初のモードの登録
	ModeServer::GetInstance()->Add(new ModeTitle(), 1, "title");
	//ModeServer::GetInstance()->Add(new GalGame(), 1, "GalGame");
	//ModeServer::GetInstance()->Add(new Action3DGame(), 2, "Action");

	return true;
}

bool ApplicationMain::Terminate() {
	ApplicationBase::Terminate();
	return true;
}


bool ApplicationMain::Input() {
	ApplicationBase::Input();
	return true;
}

bool ApplicationMain::Process() {
	ApplicationBase::Process();
	return true;
}

bool ApplicationMain::Render() {
	ApplicationBase::Render();
	return true;
}

