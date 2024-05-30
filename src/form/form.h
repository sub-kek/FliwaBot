#pragma once

#include <FliwaCord/fliwacord.h>
#include <string>

namespace FliwaBot {
    class form {
    public:
        virtual ~form() = default;

        virtual std::string get_id() = 0;

        virtual void submit(const FliwaCord::form_submit_t &event) = 0;

        static std::vector<std::unique_ptr<form>> forms;

        static void register_forms();
    };
}