#include "../Mode/GalGame.h"
#include <string>

#define novelCameraPositionEnd { 0.006049f,21.895990f,-10.059654f }
#define novelCameraPositionStart { 0.1f, 10.0f, -20.0f }
#define novelCameraTargetStart {0.0f, 10.0f, 0.0f}
#define novelCameraTargetEnd {0.006048f, 11.331523f, 12.522373f}

GalGame::GalGame() {

	_pCamera = nullptr;
	_pCharaModel = nullptr;
	_pMouseInput = nullptr;
	_pOnnaModel = nullptr;
	_pOnnaRedModel = nullptr;
	_pInput = nullptr;
	_pVectorTweenPotion = nullptr;
	_pVectorTweenTarget = nullptr;
	_pGalGameUI = nullptr;

	_favor = 0;
	_molecule = 0;
	_coin = 0;
}

GalGame::~GalGame() {
}

bool GalGame::Initialize() {

	if (!ModeBase::Initialize()) {
		return false;
	}

	_pCamera.reset(new Camera);
	_pRoomModel.reset(new Model);
	_pInput.reset(new Input);
	_pOnnaModel.reset(new AnimationBase);
	_pOnnaRedModel.reset(new AnimationBase);
	_pVectorTweenPotion.reset(new VectorTween);
	_pVectorTweenTarget.reset(new VectorTween);
	_pGalGameUI.reset(new GalGameUI);
	_pMouseInput.reset(new MouseInput);

	if (!_pGalGameUI->Init()){
		return false;	
	}

	//_pCamera->SetPosition(0.0f, 10.0f, -20.0f);
	//_pCamera->SetTarget(0.0f, 10.0f, 0.0f);
	//_pCamera->SetNearFar(0.1f, 800.0f);

	_pCamera->SetPosition(0.006049f, 21.895990f, -10.059654f);
	_pCamera->SetTarget(0.006048f, 11.331523f, 12.522373f);
	_pCamera->SetNearFar(0.1f, 800.0f);

	_pOnnaModel->Load("model/onna/onna.pmx");
	_pOnnaRedModel->Load("model/onna_red/onna_red.pmx");
	_pRoomModel->Load("model/room/roomkagu.pmx");

	_favor = 0;
	_molecule = 0;
	_coin = 5000;

	return true;
}

bool GalGame::Process() {

	if (_pMouseInput == nullptr) {
		return false;
	}
	_pMouseInput->Process();

	//SetUI
	_pGalGameUI->SetCoin(_coin);
	


	_pOnnaModel->Play(true, 0, 0.3f);
	_pOnnaRedModel->Play(true, 0, 0.3f);


	if (CheckHitKey(KEY_INPUT_D)) {
		_pOnnaModel->Play(true, 1, 5.0f);
	}

	if (CheckHitKey(KEY_INPUT_G)) {

		//途中から開始
		//_pScriptEngin->SetState(amg::ScriptEngine::ScriptState::PARSING);

	}

	if (_pInput->_key[(KEY_INPUT_Q)] == 1) {
		//終わらせる
		//_pScriptEngin->SetState(amg::ScriptEngine::ScriptState::END);

		_pVectorTweenPotion->SetVectorTween(novelCameraPositionEnd, novelCameraPositionStart, 45,VectorTween::Type::SineStart);
		_pVectorTweenTarget->SetVectorTween(novelCameraTargetEnd, novelCameraTargetStart, 45, VectorTween::Type::SineStart);
	}

	if (_pInput->_key[(KEY_INPUT_W)] == 1) {

		//_pScriptEngin->ReInitialize();
		//_pScriptEngin->SetState(amg::ScriptEngine::ScriptState::PARSING);  //スクリプト開始

		//カメラ移動
		_pVectorTweenPotion->SetVectorTween(novelCameraPositionStart, novelCameraPositionEnd, 45, VectorTween::Type::SineStart);
		_pVectorTweenTarget->SetVectorTween(novelCameraTargetStart, novelCameraTargetEnd, 45, VectorTween::Type::SineStart);
	}

	if (_pVectorTweenPotion->IsStart() && !_pVectorTweenPotion->IsEnd()) {

		VECTOR CameraPositionNow = _pVectorTweenPotion->GetPosition();
		float pX = CameraPositionNow.x, pY = CameraPositionNow.y, pZ = CameraPositionNow.z;

		_pCamera->SetPosition(pX, pY, pZ);
	}

	if (_pVectorTweenTarget->IsStart() && !_pVectorTweenTarget->IsEnd()) {

		VECTOR CameraTargetNow = _pVectorTweenTarget->GetPosition();
		float tX = CameraTargetNow.x, tY = CameraTargetNow.y, tZ = CameraTargetNow.z;

		_pCamera->SetTarget(tX, tY, tZ);
	}

	if (_pGalGameUI->GetSakeItem()) {
		_pOnnaRedModel->Process();
	}
	else {
		_pOnnaModel->Process();
	}

	if (_pGalGameUI->GetGoTitle()) {
		//_pGalGameUI->SetGoTitle(false);

		ModeServer::GetInstance()->Del(this);  // このモードを削除予約
		ModeServer::GetInstance()->Add(new GalGame(), 5, "Title");  // 次の
	}


	_pCamera->Process();
	_pRoomModel->Process();

	_pInput->Process();
	_pVectorTweenPotion->Process();
	_pVectorTweenTarget->Process();
	_pGalGameUI->Process();
	//_pScriptEngin->Update();

	return true;
}

bool GalGame::Render() {

	_pRoomModel->Render();

	if (_pGalGameUI->GetSakeItem()) {
		_pOnnaRedModel->Render();
	}
	else {
		_pOnnaModel->Render();
	}

	_pGalGameUI->Draw();
	_pMouseInput->Draw();  //最後に必ず置く

	/*
	if (_pScriptEngin->GetState()!= amg::ScriptEngine::ScriptState::END) {
		_pScriptEngin->Render();
	}
	*/

	//debug情報
	_pCamera->Render();
	//DrawFormatString(100, 900, GetColor(255, 0, 0), "好感度%d",_favor);
	//DrawFormatString(100, 930, GetColor(255, 0, 0), "分子%d", _molecule);

	return true;
}

bool GalGame::Terminate() {

	_pGalGameUI->Terminate();
	return true;
}