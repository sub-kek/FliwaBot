#include "ping_command.h"

#include "../bot.h"
#include "../utility.h"
#include "../config/language.h"
#include "../builder.h"

namespace FliwaBot {
  std::string ping_command::get_name() {
    return "ping";
  }

  std::string ping_command::get_description() {
    return "Calculate bot ping/latency and others";
  }

  void ping_command::execute(const FliwaCord::slashcommand_t &event) {
    FliwaCord::embed embed = embed_builder::get_styled_embed()
        .set_description(language::command_ping_embed_description_checking);
    const auto begin_time = std::chrono::steady_clock::now();
    thread_locker locker;

    event.reply(embed, [&locker](const FliwaCord::confirmation_callback_t &) {
        locker.complete();
    });

    locker.wait();

    const auto end_time = std::chrono::steady_clock::now();

    embed.set_description(formatter::format(language::command_ping_embed_description,
                                            {
                                                std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(
                                                    end_time - begin_time).count())
                                            }));

    event.edit_response(embed);
  }
}