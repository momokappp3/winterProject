//!
//! @file amg_string.h
//!
//! @brief std::string に対してのユーティリティ処理定義
//!
#pragma once

#include <vector>
#include <string>

namespace amg{

    namespace string{

        bool ToInt(const std::string& str, int& integer);
        bool ToFloat(const std::string& str, float& realNumber);
        std::vector<std::string> Split(const std::string& str, const std::string& delimiter);
    }
}
