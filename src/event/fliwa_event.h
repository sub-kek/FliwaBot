#pragma once

#include <FliwaCord/fliwacord.h>
#include "../bot.h"

namespace FliwaBot::event {
  void on_slashcommand(const FliwaCord::slashcommand_t &event);
  void on_ready(const FliwaCord::ready_t &event);
}