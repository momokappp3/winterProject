//!
//! @file command_novel.cpp
//!
//! @brief 'n' スクリプトを処理するクラス実装
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
