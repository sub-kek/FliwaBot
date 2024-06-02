#include "form.h"
#include "whitelist_ticket_form.h"

namespace FliwaBot {
    std::vector<std::unique_ptr<form>> form::forms;

    void form::register_forms() {
        forms.push_back(std::make_unique<whitelist_ticket_form>(whitelist_ticket_form()));
    }

    FliwaCord::interaction_modal_response form::get_form_by_id(const std::string& id) {
        for (auto &form: forms) {
            if (form->get_id() != id) continue;

            return form->get_form();
        }

        return {};
    }
}