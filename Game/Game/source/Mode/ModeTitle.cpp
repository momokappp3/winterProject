#include "../Mode/ModeTitle.h"
#include <string>
#include <Dxlib.h>
#include "../../ResourceServer.h"

#define novelCameraPositionEnd { 0.006049f,21.895990f,-10.059654f }
#define novelCameraPositionStart { 0.1f, 10.0f, -20.0f }
#define novelCameraTargetStart {0.0f, 10.0f, 0.0f}
#define novelCameraTargetEnd {0.006048f, 11.331523f, 12.522373f}

#define ScaleStage {2.230,2.230,2.230}

#define ScaleLove {0.150,0.150,0.150}
#define ScaleLoveMove {0.2,0.2,0.2}
#define PositionLove {-67.778, 18.026, 18.026}
#define PositionLove2 {-47.778, 12.026, 7.210}

#define ScaleSweet {0.070,0.070,0.070}
#define PositionSweet {-60.778,8.026,-0.721}

#define ScaleEx {0.040, 0.040, 0.040}
#define PositionEx {-43.984, 4.326,0.000}

//穴あきハート
#define Scale2Heart {0.1,0.1,0.1}  
#define Position2Heart {-15.142, 7.932, 0.000}
#define Position2Heart2 {-20.910, 7.932, 0.000}

//塗りつぶしハート
#define ScaleHeart {0.080,0.080,0.080}  
#define ScaleHeart2 {0.120,0.120,0.120}
#define PositionHeart {-58.405, 23.795, -10.095}
#define PositionHeart2 {-36.052, 23.073, 0.000}
#define RotationHeart {0.045, 5.969, 0.359}
#define RotationHeart2 {0.359, 6.149, 6.104}

ModeTitle::ModeTitle() {

	_pStageModel = nullptr;
	_pLove = nullptr;
	_pLove2 = nullptr;
	_pSweet = nullptr;
	_pHeart = nullptr;
	_pHeart2 = nullptr;
	_p2Heart = nullptr;
	_p2Heart2 = nullptr;
	_pEx = nullptr;
	_pCamera = nullptr;
	_pMouseInput = nullptr;
	_pAnimationBase = nullptr;
	_pInput = nullptr;

	//tween
	_pVectorTweenPotion = nullptr;
	_pVectorTweenTarget = nullptr;
	_pLoveTweenScale = nullptr;
}

ModeTitle::~ModeTitle() {
}

bool ModeTitle::Initialize() {

	if (!ModeBase::Initialize()) {
		return false;
	}

	//メモリの所有権を委ねるには.reset
	_pCamera.reset(new Camera);
	_pStageModel.reset(new Model);
	_pLove.reset(new Model);
	_pLove2.reset(new Model);
	_pSweet.reset(new Model);
	_pHeart.reset(new Model);
	_pHeart2.reset(new Model);
	_p2Heart.reset(new Model);
	_p2Heart2.reset(new Model);
	_pEx.reset(new Model);
	_pMouseInput.reset(new MouseInput);
	_pAnimationBase.reset(new AnimationBase);
	_pInput.reset(new Input);
	_pVectorTweenPotion.reset(new VectorTween);
	_pVectorTweenTarget.reset(new VectorTween);
	_pLoveTweenScale.reset(new VectorTween);

	_pCamera->SetPosition(-29.132515f, 31.393948f, -53.699860f);
	_pCamera->SetTarget(-31.634794f, 16.672798f, 2.017584f);
	_pCamera->SetNearFar(1.442092f, 360.523010f);

	_pStageModel->Load("model/iceStage/stage.pmx");  //ステージ
	//_pStageModel->Load("model/actionStage/Stage.mv1");  //ステージ
	_pAnimationBase->Load("model/onna/onna.pmx");  //キャラ
	_pLove->Load("model/title/title_love.mv1",true);  //文字
	_pLove2->Load("model/title/love.mv1",true);
	_pSweet->Load("model/title/title_sweetLoom.mv1");
	_pHeart->Load("model/title/titleHeart.mv1",true);
	_pHeart2->Load("model/title/titleHeart.mv1",true);
	_p2Heart->Load("model/title/titleHeart2.mv1",true);
	_p2Heart2->Load("model/title/titleHeart2.mv1",true);
	_pEx->Load("model/title/titleEx.mv1");

	/*
	//塗りつぶしハート未実装
	if (MV1SetScale(_pHeart->GetHandle(), ScaleHeart), MV1SetPosition(_pHeart->GetHandle(), PositionHeart),
		MV1SetRotationXYZ(_pHeart->GetHandle(), RotationHeart)) {
		return false;
	}

	if (MV1SetScale(_pHeart2->GetHandle(), ScaleHeart2), MV1SetPosition(_pHeart2->GetHandle(), PositionHeart2),
		MV1SetRotationXYZ(_pHeart->GetHandle(), RotationHeart2)) {
		return false;
	}
	*/

	SetModelInitInfo();

	return true;
}

bool ModeTitle::Process() {

	if (_pMouseInput == nullptr) {
		return false;
	}

	//モデルを動かす

	bool flag = false;
	
	if (false) {
		_pLoveTweenScale->SetVectorTween(ScaleLove, ScaleLoveMove, 60);

		if (_pLoveTweenScale->IsStart() && !_pLoveTweenScale->IsEnd()) {

			VECTOR Now = _pLoveTweenScale->GetPosition();
			MV1SetScale(_pLove->GetHandle(), Now);
		}
		if (_pLoveTweenScale->IsEnd()) {
			flag = true;
		}
	}
	else {
		_pLoveTweenScale->SetVectorTween(ScaleLoveMove, ScaleLove, 60);

		if (_pLoveTweenScale->IsStart() && !_pLoveTweenScale->IsEnd()) {

			VECTOR Now = _pLoveTweenScale->GetPosition();
			MV1SetScale(_pLove->GetHandle(), Now);
		}
		if (_pLoveTweenScale->IsEnd()) {
			flag = false;
		}
	}
	

	_pAnimationBase->Play(true, 0, 0.3f);

	//カメラに対して角度をつけ足せる バグ
	if (CheckHitKey(KEY_INPUT_LEFT)) {	
		_pCamera->GetTransform().AddRotateY(0.5f);
	}
	if (CheckHitKey(KEY_INPUT_RIGHT)) {
		_pCamera->GetTransform().AddRotateY(-0.5f);
	}

	if (CheckHitKey(KEY_INPUT_A)) {

		//モデルに対して角度をつけ足せる
		_pAnimationBase->GetTransform().AddRotateY(5.0f);
	}

	if (CheckHitKey(KEY_INPUT_S)) {

		//モデルに対して角度をつけ足せる
		_pAnimationBase->GetTransform().AddRotateY(-5.0f);
	}

	if (CheckHitKey(KEY_INPUT_D)) {
		_pAnimationBase->Play(true, 1, 5.0f);
	}

	if (_pInput->_key[(KEY_INPUT_Q)] == 1) {
		//終わらせる

		//_pCamera->SetPosition(0.0f, 10.0f, -20.0f);
		//_pCamera->SetTarget(0.0f, 10.0f, 0.0f);

		_pVectorTweenPotion->SetVectorTween(novelCameraPositionEnd, novelCameraPositionStart, 30);
		_pVectorTweenTarget->SetVectorTween(novelCameraTargetEnd, novelCameraTargetStart, 30);
	}

	if (_pInput->_key[(KEY_INPUT_W)] == 1) {
		//カメラ移動
		_pVectorTweenPotion->SetVectorTween(novelCameraPositionStart, novelCameraPositionEnd, 30);
		_pVectorTweenTarget->SetVectorTween(novelCameraTargetStart, novelCameraTargetEnd, 30);
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

	if (CheckHitKey(KEY_INPUT_B)) {
		_pLove2->GetTransform().AddRotateY(2.0f);
	}

	_pAnimationBase->Process();
	_pCamera->Process();
	_pStageModel->Process();
	_pLove->Process();
	_pLove2->Process();
	_pSweet->Process();
	_pHeart->Process();
	_pHeart2->Process();
	_p2Heart->Process();
	_p2Heart2->Process();
	_pEx->Process();
	_pMouseInput->Process();
	_pInput->Process();
	_pVectorTweenPotion->Process();
	_pVectorTweenTarget->Process();
	_pLoveTweenScale->Process();

	return true;
}

bool ModeTitle::Render() {

	_pCamera->Render();
	_pStageModel->Render();
	_pLove->Render();
	_pLove2->Render();
	_pSweet->Render();
	_pHeart->Render();
	_pHeart2->Render();
	_p2Heart->Render();
	_p2Heart2->Render();
	_pEx->Render();
	_pMouseInput->Draw();
	_pAnimationBase->Render();

	return true;
}

bool ModeTitle::SetModelInitInfo() {

	_pStageModel->GetTransform().SetScale(ScaleStage);

	_pLove->GetTransform().SetScale(ScaleLove); _pLove->GetTransform().SetPosition(PositionLove);
	_pLove2->GetTransform().SetScale(ScaleLove); _pLove2->GetTransform().SetPosition(PositionLove2);

	_pSweet->GetTransform().SetScale(ScaleSweet);  _pSweet->GetTransform().SetPosition(PositionSweet);

	_p2Heart->GetTransform().SetScale(Scale2Heart); _p2Heart->GetTransform().SetPosition(Position2Heart);
	_p2Heart2->GetTransform().SetScale(Scale2Heart); _p2Heart2->GetTransform().SetPosition(Position2Heart2);

	_pEx->GetTransform().SetScale(ScaleEx), _pEx->GetTransform().SetPosition(PositionEx);

	_pHeart->GetTransform().SetScale(ScaleHeart); _pHeart->GetTransform().SetPosition(PositionHeart);
	_pHeart2->GetTransform().SetScale(ScaleHeart); _pHeart2->GetTransform().SetPosition(PositionHeart2);
	_pHeart->GetTransform().SetDirection(RotationHeart);
	_pHeart2->GetTransform().SetDirection(RotationHeart2);

	return true;
}

bool ModeTitle::Terminate() {
	return true;
}