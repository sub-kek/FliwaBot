#include "reload_command.h"

#include "../bot.h"
#include "../utility.h"
#include "../config/language.h"
#include "../builder.h"
#include "../config/config.h"

namespace FliwaBot {
    std::string reload_command::get_name() {
        return config::reload_command_name;
    }

    std::string reload_command::get_description() {
        return config::reload_command_description;
    }

    void reload_command::execute(const FliwaCord::slashcommand_t &event) {
        FliwaCord::message message = FliwaCord::message()
                .set_flags(config::command_reload_ephemeral ? FliwaCord::m_ephemeral : 0);
        FliwaCord::embed embed = embed_builder::get_styled_embed()
                .set_description(language::command_reload_no_perms);

        if (event.command.usr.id.str() == config::author_id) {
            config::init("bot_config.yml");
            language::init("bot_language.yml");

            embed.set_description(language::command_reload_successfully);
        }

        message.add_embed(embed);

        event.reply(message);
    }
}