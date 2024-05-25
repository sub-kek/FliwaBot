#include "fliwa_event.h"

#include "../builder.h"
#include <chrono>

constexpr unsigned int hash(const char *s, int off = 0) {
  return !s[off] ? 5381 : (hash(s, off + 1) * 33) ^ s[off];
}

void FliwaBot::event::on_slashcommand(const FliwaCord::slashcommand_t &event) {
  event.thinking();

  using namespace std::chrono_literals;
  std::this_thread::sleep_for(std::chrono::seconds(1s)); // Test for thinking

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
          "Автор: subkek#0"
      ));

      message.add_embed(embed);

      event.edit_original_response(message);

      break;
  }
}