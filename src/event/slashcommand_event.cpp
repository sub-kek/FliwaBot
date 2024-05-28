#include "fliwa_event.h"
#include "../command/command.h"

constexpr unsigned int hash(const char *s, int off = 0) {
  return !s[off] ? 5381 : (hash(s, off + 1) * 33) ^ s[off];
}

void FliwaBot::event::on_slashcommand(const FliwaCord::slashcommand_t &event) {
  for (auto &cmd: command::commands) {
    if (event.command.get_command_name() != cmd->get_name()) continue;

    cmd->execute(event);
    break;
  }
}