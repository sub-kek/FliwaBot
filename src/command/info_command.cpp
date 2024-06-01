#include "info_command.h"

#include "../builder.h"
#include "../utility.h"

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
                        dotenv::getenv("VERSION"),
                        true
                )
                .add_field(
                        "Главный разработчик",
                        formatter::format("<@{0}>", {dotenv::getenv("AUTHOR_ID")}),
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