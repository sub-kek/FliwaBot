#include "fliwa_event.h"

#include "../builder.h"
#include "../config/config.h"
#include <chrono>

constexpr unsigned int hash(const char *s, int off = 0) {
  return !s[off] ? 5381 : (hash(s, off + 1) * 33) ^ s[off];
}

void FliwaBot::event::on_slashcommand(const FliwaCord::slashcommand_t &event) {
  switch (hash(event.command.get_command_name().data())) {
    case hash("ping"):
      event.edit_original_response("Имя бота " + bot::core->me.format_username());
      break;

    case hash("status"):
      FliwaCord::message message = FliwaCord::message();

      FliwaCord::embed embed = FliwaBot::embed_builder::get_styled_embed();
      embed.set_title("Статус Fliwa");
      embed.set_description(std::string(
          "Аптайм: " + FliwaBot::bot::core->uptime().to_string() + "\n" +
          "Автор: " + config::author_name + "\n" +
          "Кластер: " + config::cluster_name
      ));

      message.add_embed(embed);

      FliwaCord::message reply_message = FliwaCord::message()
          .set_content("Статус бота отправлен вам в личные сообщения.")
          .set_flags(FliwaCord::m_ephemeral);

      event.reply(reply_message);

      bot::core->direct_message_create(event.command.usr.id, message);

      break;
  }
}