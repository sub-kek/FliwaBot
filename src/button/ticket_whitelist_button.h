#pragma once

#include "button.h"

namespace FliwaBot {
    class ticket_whitelist_button : public button {
        std::string get_id() override;

        void click(const FliwaCord::button_click_t &event) override;
    };
}