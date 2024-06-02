#include "info_command.h"

#include "../builder.h"
#include "../utility.h"
#include "../config.h"

namespace FliwaBot {
    std::string info_command::get_name() {
        return "инфо";
    }

    std::string info_command::get_description() {
        return "Информация о боте.";
    }

    void info_command::execute(const FliwaCord::slashcommand_t &event) {
        FliwaCord::embed embed = embed_builder::get_styled_embed()
                .set_title("FliwaBot")
                .set_description("Я была создана чтобы помогать всем на этом сервере")
                .add_field(
                        "Версия",
                        formatter::format("{0} <t:{1}:d>",
                                          {config::version, config::version_timestamp}),
                        true
                )
                .add_field(
                        "Главный разработчик",
                        formatter::format("<@{0}>", {config::author_id}),
                        true
                )
                .add_field(
                        "Полезные ссылки",
                        "[Github](https://github.com/sub-kek/FliwaBot)",
                        false
                );
        event.reply(embed);
    }
}