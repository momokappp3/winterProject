#include "../Mode/Action3DGame.h"

Action3DGame::Action3DGame() {

	_pCamera = nullptr;
	_pModel = nullptr;
	_pAnimationBase = nullptr;
	_pInput = nullptr;
	//_pAnimation = nullptr;
}

Action3DGame::~Action3DGame() {
}

bool Action3DGame::Initialize() {

	if (!ModeBase::Initialize()) {
		return false;
	}

	//メモリの所有権を委ねるには.reset
	_pCamera.reset(new Camera);
	//_pModel.reset(new Model);
	_pAnimationBase.reset(new AnimationBase);
	_pInput.reset(new Input);

	_pCamera->SetPosition(0.0f,10.0f,-20.0f);
	_pCamera->SetTarget(0.0f, 10.0f, 0.0f);
	_pCamera->SetNearFar(0.1f, 800.0f);

	//_pModel->Load("model/otoko/otoko.pmx");
	_pAnimationBase->Load("model/otoko/otoko.pmx");

	return true;
}

bool Action3DGame::Process() {
	
	if (_pInput != nullptr) {
		_pInput->Process();
	}
	//_pModel->Process();
	_pAnimationBase->Process();
	_pCamera->Process();

	if (_pInput->_key[(KEY_INPUT_A)] == 1) {

		//モデルに対して角度をつけ足せる
		//_pModel->GetTransform().AddRotateY(5.0f);
		_pAnimationBase->GetTransform().AddRotateY(5.0f);
	}

	if (_pInput->_key[(KEY_INPUT_S)] == 1) {

		//モデルに対して角度をつけ足せる
		//_pModel->GetTransform().AddRotateY(-5.0f);
	}



	if (_pInput->_key[(KEY_INPUT_D)] == 1) {

		_pAnimationBase->Play(true, 0, 0.5f);

	}

	return true;
}

bool Action3DGame::Render() {

	_pCamera->Render();
	//_pModel->Render();
	_pAnimationBase->Render();
	return true;
}

bool Action3DGame::Terminate() {
	return true;
}