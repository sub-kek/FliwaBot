#include "fliwa_event.h"

void FliwaBot::event::on_ready(const FliwaCord::ready_t &event) {
  FliwaBot::bot::core->log(FliwaCord::ll_info, "Bot ready as " + FliwaBot::bot::core->me.format_username());

  FliwaBot::bot::register_slashcommands();
}