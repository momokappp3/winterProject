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
	_pAnimationBase = nullptr;
	_pScriptEngin = nullptr;
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
	_pAnimationBase.reset(new AnimationBase);
	_pVectorTweenPotion.reset(new VectorTween);
	_pVectorTweenTarget.reset(new VectorTween);
	_pScriptEngin.reset(new amg::ScriptEngine);
	_pGalGameUI.reset(new GalGameUI);
	_pMouseInput.reset(new MouseInput);

	if (!_pGalGameUI->Init()){
		return false;	
	}

	
	if (!_pScriptEngin->Initialize("source/excel/escape_from_amg1.json")) {
		return false;
	}
	

	_pCamera->SetPosition(0.0f, 10.0f, -20.0f);
	_pCamera->SetTarget(0.0f, 10.0f, 0.0f);
	_pCamera->SetNearFar(0.1f, 800.0f);

	_pAnimationBase->Load("model/onna/onna.pmx");
	//_pAnimationBase->Load("model/onna_red/onna_red.pmx");
	_pRoomModel->Load("model/room/roomkagu.pmx");

	_pScriptEngin->SetState(amg::ScriptEngine::ScriptState::END);


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

	int tmp;
	int lastFavor = _favor;

	tmp = _pScriptEngin->GetFavor();  //分子9900まで

	if (tmp > 9900) {
		tmp = 9900;
	}
	_favor = tmp / 100;
	_molecule = tmp % 100;

	if (lastFavor != _favor) {
		_pGalGameUI->SetMolecule(100);
		//_pGalGameUI->SetMolecule(0);
	}
	
	//SetUI
	_pGalGameUI->SetCoin(_coin);
	_pGalGameUI->SetFavor(_favor);
	_pGalGameUI->SetMolecule(_molecule);

	_pAnimationBase->Play(true, 0, 0.3f);


	if (CheckHitKey(KEY_INPUT_D)) {
		_pAnimationBase->Play(true, 1, 5.0f);
	}

	if (CheckHitKey(KEY_INPUT_G)) {

		//途中から開始
		_pScriptEngin->SetState(amg::ScriptEngine::ScriptState::PARSING);

	}

	if (_pInput->_key[(KEY_INPUT_Q)] == 1) {
		//終わらせる
		_pScriptEngin->SetState(amg::ScriptEngine::ScriptState::END);

		_pVectorTweenPotion->SetVectorTween(novelCameraPositionEnd, novelCameraPositionStart, 45,VectorTween::Type::SineStart);
		_pVectorTweenTarget->SetVectorTween(novelCameraTargetEnd, novelCameraTargetStart, 45, VectorTween::Type::SineStart);
	}

	if (_pInput->_key[(KEY_INPUT_W)] == 1) {

		_pScriptEngin->ReInitialize();
		_pScriptEngin->SetState(amg::ScriptEngine::ScriptState::PARSING);  //スクリプト開始

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




	_pAnimationBase->Process();
	_pCamera->Process();
	_pRoomModel->Process();

	_pInput->Process();
	_pVectorTweenPotion->Process();
	_pVectorTweenTarget->Process();
	_pGalGameUI->Process();
	_pScriptEngin->Update();

	return true;
}

bool GalGame::Render() {

	_pRoomModel->Render();
	_pAnimationBase->Render();
	_pGalGameUI->Draw();
	_pMouseInput->Draw();  //最後に必ず置く

	
	if (_pScriptEngin->GetState()!= amg::ScriptEngine::ScriptState::END) {
		_pScriptEngin->Render();
	}

	//debug情報
	_pCamera->Render();
	DrawFormatString(100, 900, GetColor(255, 0, 0), "好感度%d",_favor);
	DrawFormatString(100, 930, GetColor(255, 0, 0), "分子%d", _molecule);

	return true;
}

bool GalGame::Terminate() {

	_pScriptEngin->Destroy();
	return true;
}