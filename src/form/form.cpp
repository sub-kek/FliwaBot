#include "form.h"

namespace FliwaBot {
    std::vector<std::unique_ptr<form>> form::forms;

    void form::register_forms() {
        //form.push_back(std::make_unique<whitelist_ticket_form>(whitelist_ticket_form()));
    }
}