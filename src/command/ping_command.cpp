#include <FliwaCord/unicode_emoji.h>

#include "ping_command.h"
#include "../bot.h"
#include "../utility.h"
#include "../config/language.h"
#include "../builder.h"
#include "../config/config.h"

namespace FliwaBot {
    std::string ping_command::get_name() {
        return config::ping_command_name;
    }

    std::string ping_command::get_description() {
        return config::ping_command_description;
    }

    void ping_command::execute(const FliwaCord::slashcommand_t &event) {
        FliwaCord::message message = FliwaCord::message();

        message.add_component(
                FliwaCord::component().add_component(
                        FliwaCord::component()
                                .set_type(FliwaCord::cot_button)
                                .set_emoji(FliwaCord::unicode_emoji::two_hearts)
                                .set_label("Form")
                                .set_style(FliwaCord::cos_success)
                                .set_id("button_lol")
                )

        );

        FliwaCord::embed embed = embed_builder::get_styled_embed()
                .set_description(language::command_ping_embed_description_checking);
        const auto begin_time = std::chrono::steady_clock::now();
        auto *locker = new thread_locker();

        event.reply(message.add_embed(embed), [&locker](const FliwaCord::confirmation_callback_t &) {
            locker->complete();
        });

        locker->wait();

        const auto end_time = std::chrono::steady_clock::now();

        embed.set_description(formatter::format(language::command_ping_embed_description,
                                                {
                                                        std::to_string(
                                                                std::chrono::duration_cast<std::chrono::milliseconds>(
                                                                        end_time - begin_time).count())
                                                }));

        message.embeds[0] = embed;

        event.edit_original_response(message);
    }
}