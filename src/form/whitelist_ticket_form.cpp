#include <regex>

#include "whitelist_ticket_form.h"
#include "../bot.h"
#include "../builder.h"
#include "../utility.h"

namespace FliwaBot {
    std::string whitelist_ticket_form::get_id() {
        return "whitelist_ticket_form";
    }

    FliwaCord::interaction_modal_response whitelist_ticket_form::get_form() {
        return FliwaCord::interaction_modal_response()
                .set_title("Заявка на сервер")
                .add_component(
                        FliwaCord::component()
                                .set_label("Ваш игровой ник")
                                .set_id("nickname")
                                .set_placeholder("Steve")
                                .set_type(FliwaCord::cot_text)
                                .set_text_style(FliwaCord::text_short)
                                .set_max_length(16)
                                .set_min_length(3))
                .add_row()
                .add_component(
                        FliwaCord::component()
                                .set_label("Ваш возвраст")
                                .set_id("age")
                                .set_placeholder("15")
                                .set_type(FliwaCord::cot_text)
                                .set_text_style(FliwaCord::text_short)
                                .set_max_length(2)
                                .set_min_length(1))
                .set_custom_id(get_id());
    }

    void whitelist_ticket_form::submit(const FliwaCord::form_submit_t &event) {
        std::string nickname = std::get<std::string>(event.components[0].components[0].value);
        std::string age_str = std::regex_replace(std::get<std::string>(event.components[1].components[0].value),
                                                 std::regex("[^0-9]+"), "");

        FliwaCord::message message = FliwaCord::message()
                .add_embed(
                        embed_builder::get_styled_embed()
                                .set_title("Тикет создан")
                                .set_description(
                                        formatter::format(
                                                "Вы можете посмотреть его здесь <#{0}>\n"
                                                "Nick: `{1}`\n"
                                                "Age: {2}",
                                                {
                                                        "temp empty",
                                                        nickname,
                                                        age_str
                                                })
                                )
                )
                .set_flags(FliwaCord::m_ephemeral);

        event.reply(message);
    }
}