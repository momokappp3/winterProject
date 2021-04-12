#include "command_face.h"
#include "amg_string.h"

namespace {
    constexpr size_t SCRIPT_NUM = 7;
}

namespace amg {
    CommandFace::CommandFace(unsigned int line, const std::vector<std::string>& script)
        : CommandBase(line, script) {
        _faceNum = -1;
        _min = 0.0f;
        _max = 0.0f;
        _tweenFrame = 0;
        _stopTime = 0;
        _delay = 0;
    }

    bool CommandFace::Check() {
        const auto size = script.size();

        if (size != SCRIPT_NUM) {
            return false;
        }

        auto value = 0;

        if (!string::ToInt(script[1], value)) {
            return false;
        }

        _faceNum = value;

        auto valueF = 0.0f;

        if (!string::ToFloat(script[2], valueF)) {
            return false;
        }

        _min = valueF;

        if (!string::ToFloat(script[3], valueF)) {
            return false;
        }

        _max = valueF;

        if (!string::ToInt(script[4], value)) {
            return false;
        }

        _tweenFrame = value;

        if (!string::ToInt(script[5], value)) {
            return false;
        }

        _stopTime = value;

        if (!string::ToInt(script[6], value)) {
            return false;
        }

        _delay = value;

        return true;
    }
}
