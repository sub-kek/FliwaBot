#pragma once

#include "command.h"

namespace FliwaBot {
    class status_command : public command {
    public:
        std::string get_name() override;

        std::string get_description() override;

        void execute(const FliwaCord::slashcommand_t &event) override;
    };
}