#pragma once

#include "form.h"

namespace FliwaBot {
    class whitelist_ticket_form : public form {
    public:
        std::string get_id() override;

        FliwaCord::interaction_modal_response get_form() override;

        void submit(const FliwaCord::form_submit_t &event) override;
    };
}
