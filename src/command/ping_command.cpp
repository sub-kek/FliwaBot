#include <ctime>

#include "ping_command.h"
#include "../bot.h"
#include "../utility.h"
#include "../builder.h"

namespace FliwaBot {
    std::string ping_command::get_name() {
        return "пинг";
    }

    std::string ping_command::get_description() {
        return "Пинг и \"латенси\" бота до api.";
    }

    void ping_command::execute(const FliwaCord::slashcommand_t &event) {
        FliwaCord::embed embed = embed_builder::get_styled_embed()
                .set_description("Тестирование");

        const auto &begin_time = std::chrono::steady_clock::now();

        auto *locker = new thread_locker;

        event.reply(embed, [&locker](const FliwaCord::confirmation_callback_t &) {
            locker->complete();
        });

        locker->wait();

        const auto &end_time = std::chrono::steady_clock::now();

        embed.set_description(formatter::format("Латенси: {0}мс",
                                                {
                                                        std::to_string(
                                                                std::chrono::duration_cast<std::chrono::milliseconds>(
                                                                        end_time - begin_time).count())
                                                }));

        event.edit_original_response(embed);
    }
}