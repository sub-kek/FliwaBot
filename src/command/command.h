#pragma once

#include <FliwaCord/fliwacord.h>
#include <string>

namespace FliwaBot {
  class command {
  public:
    virtual ~command() = default;

    virtual std::string get_name() = 0;

    virtual std::string get_description() = 0;

    virtual void execute(const FliwaCord::slashcommand_t &event) = 0;

    static std::vector<std::unique_ptr<command>> commands;

    static void register_commands();
  };
}