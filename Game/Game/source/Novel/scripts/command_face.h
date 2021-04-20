#pragma once
#include "command_base.h"

namespace amg {  //int faceNum, float min, float max, int twwenFrame ,int stopTime ,int delay
    class CommandFace final : public CommandBase {
    public:
        CommandFace(unsigned int line, const std::vector<std::string>& script);
        CommandFace(const CommandFace&) = default;
        CommandFace(CommandFace&&) noexcept = default;

        virtual ~CommandFace() = default;

        CommandFace& operator=(CommandFace const& right) = default;
        CommandFace& operator=(CommandFace&& right) = default;

        bool Check() override;
        
        inline int GetFaceNum() const {  //‚±‚±‚Å—Ž‚¿‚½

            return _faceNum; 
        }
        inline float GetMin() const { 
            return _min; 
        }
        inline float GetMax() const { 
            return _max; 
        }
        inline int GetTweenFrame() const { 
            return _tweenFrame;
        }
        inline int GetStopTime() const { 
            return _stopTime; 
        }
        inline int GetDelay() const {
            return _delay; 
        }
        
    private:
        int _faceNum;
        float _min;
        float _max;
        int _tweenFrame;
        int _stopTime;
        int _delay;
    };
}