#include "fliwa_event.h"
#include "../command/command.h"

void FliwaBot::event::on_slashcommand(const FliwaCord::slashcommand_t &event) {
    for (auto &cmd: command::commands) {
        if (event.command.get_command_name() != cmd->get_name()) continue;

        cmd->execute(event);
        break;
    }
}