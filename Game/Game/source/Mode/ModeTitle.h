#pragma once
#include "appframe.h"
#include <memory>
#include "../../Camera.h"
#include "../../Model.h"
#include "../../AppFrame/MouseInput.h"
#include "../../AnimationBase.h"
#include "../.././../../AppFrame/Input.h"
#include "../../../../AppFrame/VectorTween.h"

class ModeTitle : public ModeBase {
public:
	ModeTitle();
	virtual ~ModeTitle();

	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

private:

	bool SetModelInitInfo();

	std::unique_ptr<Camera> _pCamera;
	std::unique_ptr<Model> _pStageModel;
	std::unique_ptr<Model> _pLove;
	std::unique_ptr<Model> _pLove2;
	std::unique_ptr<Model> _pSweet;
	std::unique_ptr<Model> _pHeart;
	std::unique_ptr<Model> _pHeart2;
	std::unique_ptr<Model> _p2Heart;
	std::unique_ptr<Model> _p2Heart2;
	std::unique_ptr<Model> _pEx;
	std::unique_ptr<MouseInput> _pMouseInput;
	std::unique_ptr<AnimationBase> _pAnimationBase;
	std::unique_ptr<Input> _pInput;
	std::unique_ptr<VectorTween> _pVectorTweenPotion;
	std::unique_ptr<VectorTween> _pVectorTweenTarget;
	std::unique_ptr<VectorTween> _pLoveTweenScale;
};
