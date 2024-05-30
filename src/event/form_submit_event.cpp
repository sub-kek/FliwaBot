#include "fliwa_event.h"
#include "../form/form.h"

void FliwaBot::event::on_form_submit(const FliwaCord::form_submit_t &event) {
    for (auto &form: form::forms) {
        if (form->get_id() != event.custom_id) continue;

        form->submit(event);
        break;
    }
}