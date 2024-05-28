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

    static void logger(const FliwaCord::log_t &event);
    static void log(const FliwaCord::loglevel& severity, const std::string& message);
  };
}