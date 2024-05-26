#include "bot.h"
#include "config/config.h"
#include "config/language.h"

#include "event/fliwa_event.h"

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
    core->global_command_create(FliwaCord::slashcommand("ping", "Проверка пинга бота.", core->me.id));
    core->global_command_create(FliwaCord::slashcommand("status", "Базовая информация о боте и прочее.", core->me.id));
  }

  void bot::init() {
    core = new FliwaCord::cluster(start_data::token, start_data::intents);
    core->on_log(FliwaCord::utility::cout_logger());
    config::init("bot_config.yml");
    language::init("bot_language.yml");
  }
}