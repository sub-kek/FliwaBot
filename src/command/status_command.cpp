#include "status_command.h"

#include "../bot.h"
#include "../builder.h"
#include "../utility.h"
#include "../config/config.h"
#include "../config/language.h"

namespace FliwaBot {
  std::string status_command::get_name() {
    return "status";
  }

  std::string status_command::get_description() {
    return "Get base cluster status";
  }

  void status_command::execute(const FliwaCord::slashcommand_t &event) {
    FliwaCord::message message = FliwaCord::message()
        .add_embed(FliwaBot::embed_builder::get_styled_embed()
                       .set_title(language::command_status_embed_title)
                       .set_description(formatter::format(language::command_status_embed_description,
                                                          {
                                                              bot::core->uptime().to_string(),
                                                              config::cluster_name,
                                                              config::author_name,
                                                          })))
        .set_flags(config::command_status_ephemeral ? FliwaCord::m_ephemeral : 0);
    FliwaCord::message reply_message = FliwaCord::message()
        .set_content(language::command_status_reply_text)
        .set_flags(config::command_status_ephemeral ? FliwaCord::m_ephemeral : 0);

    if (config::command_status_send_dm)
      bot::core->direct_message_create(event.command.usr.id, message);

    event.reply(config::command_status_send_dm ? reply_message : message);
  }
}