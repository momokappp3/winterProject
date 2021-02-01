//!
//! @file command_novel.cpp
//!
//! @brief 'n' �X�N���v�g����������N���X����
//!
#include "command_novel.h"

namespace {
    constexpr size_t SCRIPT_NUM = 2;
}

namespace amg{

    CommandNovel::CommandNovel(unsigned int line, const std::vector<std::string>& script)
        : CommandBase(line, script) {
        right_goal = 0;
    }

    bool CommandNovel::Check(){

        const auto size = script.size();

        if (size != SCRIPT_NUM) {
            return false;
        }

        return true;
    }
}
