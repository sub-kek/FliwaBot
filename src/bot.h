#pragma once

#include <FliwaCord/fliwacord.h>

namespace FliwaBot {
  class bot {

  public:
    struct start_data {
      static std::string token;
      static FliwaCord::intents intents;
    };

    static void init();

    static bool start();

    static void register_events();

    static void register_slashcommands();

    static FliwaCord::cluster *core;
  };
}