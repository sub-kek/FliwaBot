#pragma once

#include "form.h"

namespace FliwaBot {
    class whitelist_ticket_form : public form {
    public:
        std::string get_id();

        void submit(const FliwaCord::form_submit_t &event);
    };
}
