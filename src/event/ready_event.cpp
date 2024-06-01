#include "fliwa_event.h"

#include "../bot.h"

void FliwaBot::event::on_ready(const FliwaCord::ready_t &) {
    FliwaBot::bot::core->log(FliwaCord::ll_info, "Bot ready as " + FliwaBot::bot::core->me.format_username());

    FliwaBot::bot::register_slashcommands();
    FliwaBot::bot::register_forms();
    FliwaBot::bot::register_buttons();
}