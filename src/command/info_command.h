#pragma once

#include "command.h"

namespace FliwaBot {
  class info_command : public command {
    std::string get_name() override;
    std::string get_description() override;
    void execute(const FliwaCord::slashcommand_t &event) override;
  };
}