#include "button.h"

namespace FliwaBot {
    std::vector<std::unique_ptr<button>> button::buttons;

    void button::register_buttons() {
        //form.push_back(std::make_unique<whitelist_ticket_button>(whitelist_ticket_button()));
    }
}