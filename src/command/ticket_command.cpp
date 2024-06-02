#include "ticket_command.h"
#include "../builder.h"

namespace FliwaBot {
    std::string ticket_Command::get_name() {
        return "тикет";
    }

    std::string ticket_Command::get_description() {
        return "Создать тикет";
    }

    void ticket_Command::execute(const FliwaCord::slashcommand_t &event) {
        FliwaCord::message message = FliwaCord::message()
                .set_flags(FliwaCord::m_ephemeral);

        FliwaCord::embed embed;

        embed = embed_builder::get_styled_embed()
                .set_title("Заявка в вайтлист")
                .set_description("Отправляй только если ты новичек или хочешь сменить ник.");
        embed.footer.reset();
        message.add_embed(embed);
        FliwaCord::component whitelist_button
                = FliwaCord::component()
                        .set_id("ticket_whitelist_button")
                        .set_style(FliwaCord::cos_success)
                        .set_label("Вайтлист")
                        .set_type(FliwaCord::cot_button);

        embed = embed_builder::get_styled_embed()
                .set_title("Ошибки и прочие СЕРВЕРНЫЕ проблемы")
                .set_description("Если нашел(а) баг/дюп/лаги на сервере");
        message.add_embed(embed);
        FliwaCord::component bugs_button = FliwaCord::component()
                .set_id("ticket_server_bugs_button")
                .set_style(FliwaCord::cos_danger)
                .set_label("Ошибки")
                .set_type(FliwaCord::cot_button);

        message.add_component(FliwaCord::component()
                        .add_component(whitelist_button)
                        .add_component(bugs_button)
                        .set_type(FliwaCord::cot_action_row));

        event.reply(message);
    }
}