#pragma once
#include <memory>
#include "../../../AppFrame/VectorTween.h"

class Face {
public:
    Face();
    virtual ~Face();

    bool Init(int handle);
    void Process();

    void SetInfo(int faceNum, float min, float max, int rate, int stopTime = 0);

private:
    std::unique_ptr<VectorTween> _pFaceTween;
    int _tweenFrame;
    
    float _min;
    float _max;

    int _modelHandle;
    int _faceNum;

    bool _loop;

    int _stopTime;
};