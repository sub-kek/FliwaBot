#include "ticket_whitelist_button.h"
#include "../form/whitelist_ticket_form.h"

namespace FliwaBot {
    std::string ticket_whitelist_button::get_id() {
        return "ticket_whitelist_button";
    }

    void ticket_whitelist_button::click(const FliwaCord::button_click_t &event) {
        event.dialog(whitelist_ticket_form::get_form_by_id("whitelist_ticket_form"));
    }
}