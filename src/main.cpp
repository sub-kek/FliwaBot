#include <FliwaCord/fliwacord.h>

#include "utility.h"
#include "bot.h"

int main() {
  FliwaBot::dotenv::init(FliwaBot::dotenv::Preserve);

  FliwaBot::bot::start_data::token = FliwaBot::dotenv::getenv("TOKEN");
  FliwaBot::bot::start_data::intents = FliwaCord::i_all_intents;

  FliwaBot::bot::init();

  FliwaBot::bot::register_events();
  FliwaBot::bot::start();

  return 0;
}