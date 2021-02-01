//!
//! @file command_message.h
//!
//! @brief 'n' スクリプトを処理するクラス定義
//! 追加
#pragma once

#include "command_base.h"
#include "amg_rect.h"
#include <string>

namespace amg{

    class CommandNovel final : public CommandBase {
    public:
        CommandNovel(unsigned int line, const std::vector<std::string>& script);
        CommandNovel(const CommandNovel&) = default;
        CommandNovel(CommandNovel&&) noexcept = default;

        virtual ~CommandNovel() = default;

        CommandNovel& operator=(const CommandNovel& right) = default;
        CommandNovel& operator=(CommandNovel&& right) noexcept = default;

        bool Check() override;

        inline void Initialize(Rect&& area, const int goal) {
            this->area = area; right_goal = goal;
        }

        inline std::string GetMessage() const { return script[1]; }
        inline const Rect& GetArea() const { return area; }
        inline int GetRightGoal() const { return right_goal; }

        inline void UpdateAreaRight(const int right) { area.right = right; }

    private:
        Rect area;
        int right_goal;
    };
}