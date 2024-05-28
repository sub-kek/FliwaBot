#include <chrono>

#include "fliwa_event.h"
#include "../config/config.h"
#include "../config/language.h"
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

  // Soon i'll remove it
  switch (hash(event.command.get_command_name().data())) {
    case hash("reload"): {
      FliwaCord::message message = FliwaCord::message()
          .set_content(language::command_reload_no_perms)
          .set_flags(config::command_reload_ephemeral ? FliwaCord::m_ephemeral : 0);

      if (event.command.usr.id.str() == config::author_id) {
        config::init("bot_config.yml");
        language::init("bot_language.yml");

        message.set_content(language::command_reload_successfully);
      }

      event.reply(message);

      break;
    }
  }
}