#include "button.h"
#include "ticket_whitelist_button.h"

namespace FliwaBot {
    std::vector<std::unique_ptr<button>> button::buttons;

    void button::register_buttons() {
        buttons.push_back(std::make_unique<ticket_whitelist_button>(ticket_whitelist_button()));
    }
}