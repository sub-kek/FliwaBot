#include "status_command.h"

#include "../bot.h"
#include "../builder.h"
#include "../utility.h"

namespace FliwaBot {
    std::string status_command::get_name() {
        return "статус";
    }

    std::string status_command::get_description() {
        return "Текущий статус бота.";
    }

    void status_command::execute(const FliwaCord::slashcommand_t &event) {
        FliwaCord::embed embed = FliwaBot::embed_builder::get_styled_embed()
                .set_title("Мой статус")
                .set_description(formatter::format("Аптайм: {0}",
                                                   {
                                                           bot::core->uptime().to_string(),
                                                   }));

        event.reply(embed);
    }
}