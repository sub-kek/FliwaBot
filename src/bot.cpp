#include "bot.h"
#include "config/config.h"
#include "config/language.h"
#include "event/fliwa_event.h"
#include "command/command.h"
#include "utility.h"

namespace FliwaBot {
  FliwaCord::cluster *bot::core = nullptr;
  std::string bot::start_data::token;
  FliwaCord::intents bot::start_data::intents;

  bool bot::start() {
    core->start(FliwaCord::st_wait);
    return true;
  }

  void bot::register_events() {
    core->on_slashcommand(event::on_slashcommand);
    core->on_ready(event::on_ready);
  }

  void bot::register_slashcommands() {
    command::register_commands();

    for (auto &cmd: command::commands) {
      core->global_command_create(FliwaCord::slashcommand(cmd->get_name(), cmd->get_description(), core->me.id),
                                  [&](const FliwaCord::confirmation_callback_t &callback) {
                                      if (!callback.is_error())
                                        core->log(FliwaCord::ll_info,
                                                  formatter::format("Successfully registered command {0} - {1}",
                                                                    {cmd->get_name(), cmd->get_description()}));
                                      else
                                        core->log(FliwaCord::ll_error,
                                                  formatter::format("Error while registering command {0} - {1}",
                                                                    {cmd->get_name(), cmd->get_description()}));
                                  });
    }
  }

  void bot::init() {
    core = new FliwaCord::cluster(start_data::token, start_data::intents);
    core->on_log(FliwaCord::utility::cout_logger());
    config::init("bot_config.yml");
    language::init("bot_language.yml");
  }
}