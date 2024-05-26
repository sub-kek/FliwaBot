#include "language.h"

#include "../bot.h"

namespace FliwaBot {
  YAML::Node language::language_file;

  std::string language::command_status_embed_description;

  void language::init(const char *file_path) {
    language_file = YAML::LoadFile(file_path);
    bot::core->log(FliwaCord::ll_info, "Language loaded from: " + std::string(file_path) + ".");

    command_status_embed_description = language_file["command-status-embed-description"].as<std::string>();
  }
}