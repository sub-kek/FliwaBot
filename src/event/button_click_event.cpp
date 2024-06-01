#include "fliwa_event.h"
#include "../button/button.h"

void FliwaBot::event::on_button_click(const FliwaCord::button_click_t &event) {
    for (auto &button: button::buttons) {
        if (button->get_id() != event.custom_id) continue;

        button->click(event);
        break;
    }
}