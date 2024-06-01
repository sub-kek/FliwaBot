#pragma once

#include <FliwaCord/fliwacord.h>
#include <string>

namespace FliwaBot {
    class button {
    public:
        virtual ~button() = default;

        virtual std::string get_id() = 0;

        virtual void click(const FliwaCord::button_click_t &event) = 0;

        static std::vector<std::unique_ptr<button>> buttons;

        static void register_buttons();
    };
}