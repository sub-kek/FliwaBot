#include "command.h"
#include "ping_command.h"
#include "status_command.h"
#include "info_command.h"
#include "ticket_command.h"

namespace FliwaBot {
    std::vector<std::unique_ptr<command>> command::commands;

    void command::register_commands() {
        commands.push_back(std::make_unique<ping_command>(ping_command()));
        commands.push_back(std::make_unique<status_command>(status_command()));
        commands.push_back(std::make_unique<info_command>(info_command()));
        commands.push_back(std::make_unique<ticket_Command>(ticket_Command()));
    }
}