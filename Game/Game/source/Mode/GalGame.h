#pragma once
#include "../../AppFrame/source/appframe.h"
#include <memory>
#include "../../Camera.h"
#include "../../Model.h"
#include "../../AppFrame/MouseInput.h"
#include "../../AnimationBase.h"
#include "../Novel/scripts/script_engine.h"
#include "../.././../../AppFrame/Input.h"
#include "../../../../AppFrame/VectorTween.h"

class GalGame : public ModeBase {
public:
	GalGame();
	virtual ~GalGame();

	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

	void SetFavor(int favor) {
		_favor = favor;
	}

private:

	std::unique_ptr<Camera> _pCamera;
	std::unique_ptr<Model> _pCharaModel;
	std::unique_ptr<Model> _pRoomModel;
	std::unique_ptr<MouseInput> _pMouseInput;
	std::unique_ptr<AnimationBase> _pAnimationBase;
	std::unique_ptr<amg::ScriptEngine> _pScriptEngin;
	std::unique_ptr<Input> _pInput;
	std::unique_ptr<VectorTween> _pVectorTweenPotion;
	std::unique_ptr<VectorTween> _pVectorTweenTarget;

	int _favor;  //çDä¥ìx

};