#pragma once

#include <FliwaCord/fliwacord.h>

namespace FliwaBot::event {
    void on_slashcommand(const FliwaCord::slashcommand_t &event);

    void on_ready(const FliwaCord::ready_t &event);

    void on_form_submit(const FliwaCord::form_submit_t &event);
}