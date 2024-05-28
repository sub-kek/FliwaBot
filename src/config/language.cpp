#include <FliwaCord/fliwacord.h>
#include <string>

#include "language.h"
#include "../bot.h"

namespace FliwaBot {
  YAML::Node language::language_file;

  std::string language::command_status_embed_description;
  std::string language::command_status_embed_title;
  std::string language::command_status_reply_text;
  std::string language::command_reload_no_perms;
  std::string language::command_reload_successfully;
  std::string language::command_ping_embed_description_checking;
  std::string language::command_ping_embed_description;
  std::string language::info_command_embed_title;
  std::string language::info_command_embed_description;
  std::string language::info_command_embed_field_build_name;
  std::string language::info_command_embed_field_build_value;
  std::string language::info_command_embed_field_developer_name;
  std::string language::info_command_embed_field_developer_value;

  void language::init(const char *file_path) {
    language_file = YAML::LoadFile(file_path);
    bot::log(FliwaCord::ll_info, "Language loaded from: " + std::string(file_path) + ".");

    command_status_embed_description = language_file["command-status-embed-description"].as<std::string>();
    command_status_embed_title = language_file["command-status-embed-title"].as<std::string>();
    command_status_reply_text = language_file["command-status-reply-text"].as<std::string>();
    command_reload_no_perms = language_file["command-reload-no-perms"].as<std::string>();
    command_reload_successfully = language_file["command-reload-successfully"].as<std::string>();
    command_ping_embed_description_checking = language_file["command-ping-embed-description-checking"].as<std::string>();
    command_ping_embed_description = language_file["command-ping-embed-description"].as<std::string>();
    info_command_embed_title = language_file["info-command-embed-title"].as<std::string>();
    info_command_embed_description = language_file["info-command-embed-description"].as<std::string>();
    info_command_embed_field_build_name = language_file["info-command-embed-field-build-name"].as<std::string>();
    info_command_embed_field_build_value = language_file["info-command-embed-field-build-value"].as<std::string>();
    info_command_embed_field_developer_name = language_file["info-command-embed-field-developer-name"].as<std::string>();
    info_command_embed_field_developer_value = language_file["info-command-embed-field-developer-value"].as<std::string>();
  }
}