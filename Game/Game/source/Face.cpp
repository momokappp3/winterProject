#include "Face.h"
#include "DxLib.h"

Face::Face() {
    _pFaceTween = nullptr;
    _tweenFrame = -1;

    _faceNum = -1;
    _loop = false;

    _stopTime = 0;
}

Face::~Face() {
}

bool Face::Init(int handle) {

    if (handle == -1) {
        return false;
    }

    _modelHandle = handle;
    _pFaceTween.reset(new VectorTween);

    return true;
}

void Face::Process() {

    if (_pFaceTween->IsStart()) {
        MV1SetShapeRate(_modelHandle, _faceNum, _pFaceTween->GetPosition().x);
    }

    //ƒ‹[ƒv‚³‚¹‚é 
    if (_pFaceTween->IsEnd()) {
        if (_loop && _stopTime == 0) {  //1‰ñ–Ú‚ªI‚í‚Á‚½‚ç‹tÄ¶
            _pFaceTween->SetVectorTween({ _max,0.0,0.0 }, { _min, 0.0, 0.0 }, _tweenFrame, VectorTween::Type::SineEnd);
            _loop = false;
        }
        /*
        else {
            _pFaceTween->SetVectorTween({ _max,0,0 }, { _min, 0, 0 }, _tweenFrame, VectorTween::Type::SineEnd);
            _loop = false;
        }
        */
    }

    if (_stopTime > 0) {
        _stopTime--;
    }

    _pFaceTween->Process();
}

//loop 1‰ñ•ª•Ï‰»
void Face::SetInfo(int faceNum, float min, float max, int twwenFrame ,int stopTime) {

    if (_pFaceTween->IsStart()) {
        MV1SetShapeRate(_modelHandle, _faceNum, 0.0);
    }

    _faceNum = faceNum;
    _min = min;
    _max = max;
    _tweenFrame = twwenFrame;

    _pFaceTween->SetVectorTween({ min,0.0,0.0 }, { max, 0.0, 0.0 }, _tweenFrame, VectorTween::Type::SineEnd);
    _loop = true;

    _stopTime = stopTime;
}