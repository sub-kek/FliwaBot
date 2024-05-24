#include <FliwaCord/fliwacord.h>

#include <iostream>

#include "utility.h"
#include "builder.h"

int main() {
  FliwaBot::dotenv::init(FliwaBot::dotenv::Preserve);

  const std::string _token = FliwaBot::dotenv::getenv("TOKEN");

#define TOKEN _token

  FliwaCord::cluster bot(TOKEN, FliwaCord::i_all_intents);
  bot.on_log(FliwaCord::utility::cout_logger());

  bot.on_ready([&bot](FliwaCord::ready_t event) {
      bot.log(FliwaCord::ll_info, "Bot started as user: " + bot.me.format_username());
  });

  bot.on_message_create([&bot](FliwaCord::message_create_t event) {
      if (event.msg.author.id.str() == "667782570955767829" && event.msg.content == "Fliwa shutdown") {
        FliwaCord::message message_to_send = FliwaCord::message();
        message_to_send.set_channel_id(event.msg.channel_id);
        message_to_send.set_content("Bot shutdown now!");

        bot.message_create_sync(message_to_send);
        bot.shutdown();
      }

      if (event.msg.author.id.str() == "667782570955767829" && event.msg.content == "Fliwa info") {
        FliwaCord::message message_to_send = FliwaCord::message();
        message_to_send.set_channel_id(event.msg.channel_id);

        FliwaCord::embed send_embed = FliwaBot::embed_builder::get_styled_embed();
        send_embed.set_title("FliwaBot");
        send_embed.set_description("Test description eee");

        message_to_send.add_embed(send_embed);

        bot.message_create(message_to_send);
      }
  });

  bot.start(FliwaCord::st_wait);

  return 0;
}