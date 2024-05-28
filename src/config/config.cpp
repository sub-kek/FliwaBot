#include <FliwaCord/fliwacord.h>
#include <string>

#include "config.h"
#include "../bot.h"

namespace FliwaBot {
  YAML::Node config::language_file;

  std::string config::license_footer;
  std::string config::cluster_name;
  std::string config::author_name;
  std::string config::author_id;
  bool config::command_status_send_dm;
  bool config::command_status_ephemeral;
  bool config::command_reload_ephemeral;

  void config::init(const char *file_path) {
    language_file = YAML::LoadFile(file_path);
    bot::log(FliwaCord::ll_info, "Configuration loaded from: " + std::string(file_path) + ".");

    license_footer = language_file["license-footer"].as<std::string>();
    cluster_name = language_file["cluster-name"].as<std::string>();
    author_name = language_file["author-name"].as<std::string>();
    author_id = language_file["author-id"].as<std::string>();
    command_status_send_dm = language_file["command-status-send-dm"].as<bool>();
    command_status_ephemeral = language_file["command-status-ephemeral"].as<bool>();
    command_reload_ephemeral = language_file["command-reload-ephemeral"].as<bool>();
  }
}