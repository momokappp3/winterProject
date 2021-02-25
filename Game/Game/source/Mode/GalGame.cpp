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

	_favor = 0;
}

GalGame::~GalGame() {
}

bool GalGame::Initialize() {

	if (!ModeBase::Initialize()) {
		return false;
	}

	_pCamera.reset(new Camera);
	_pRoomModel.reset(new Model);
	_pMouseInput.reset(new MouseInput);
	_pAnimationBase.reset(new AnimationBase);
	_pScriptEngin.reset(new amg::ScriptEngine);
	_pInput.reset(new Input);
	_pVectorTweenPotion.reset(new VectorTween);
	_pVectorTweenTarget.reset(new VectorTween);

	if (!_pScriptEngin->Initialize("source/excel/escape_from_amg1.json")) {
		return false;
	}

	_pCamera->SetPosition(0.0f, 10.0f, -20.0f);
	_pCamera->SetTarget(0.0f, 10.0f, 0.0f);
	_pCamera->SetNearFar(0.1f, 800.0f);

	_pAnimationBase->Load("model/onna/onna.pmx");
	_pRoomModel->Load("model/room/roomkagu.pmx");

	_pScriptEngin->SetState(amg::ScriptEngine::ScriptState::END);

	return true;
}

bool GalGame::Process() {

	if (_pMouseInput == nullptr) {
		return false;
	}

	_favor = _pScriptEngin->GetFavor();

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

		//_pCamera->SetPosition(0.0f, 10.0f, -20.0f);
		//_pCamera->SetTarget(0.0f, 10.0f, 0.0f);

		_pVectorTweenPotion->SetVectorTween(novelCameraPositionEnd, novelCameraPositionStart, 45,VectorTween::Type::SineStart);
		_pVectorTweenTarget->SetVectorTween(novelCameraTargetEnd, novelCameraTargetStart, 45, VectorTween::Type::SineStart);
	}

	if (_pInput->_key[(KEY_INPUT_W)] == 1) {
		//スクリプト開始
		_pScriptEngin->SetState(amg::ScriptEngine::ScriptState::PARSING);

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
	_pMouseInput->Process();
	_pInput->Process();
	_pVectorTweenPotion->Process();
	_pVectorTweenTarget->Process();
	_pScriptEngin->Update();

	return true;
}

bool GalGame::Render() {

	_pCamera->Render();
	_pRoomModel->Render();
	_pMouseInput->Draw();
	_pAnimationBase->Render();

	if (_pScriptEngin->GetState()!= amg::ScriptEngine::ScriptState::END) {
		_pScriptEngin->Render();
	}

	//debug情報

	DrawFormatString(100, 900, GetColor(255, 0, 0), "好感度%d",_favor);

	return true;
}

bool GalGame::Terminate() {

	_pScriptEngin->Destroy();
	return true;
}

/*


	if (CheckHitKey(KEY_INPUT_A)) {

		//モデルに対して角度をつけ足せる
		_pAnimationBase->GetTransform().AddRotateY(5.0f);
	}

	if (CheckHitKey(KEY_INPUT_S)) {

		//モデルに対して角度をつけ足せる
		_pAnimationBase->GetTransform().AddRotateY(-5.0f);
	}

*/