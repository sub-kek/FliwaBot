#include <FliwaCord/fliwacord.h>
#include <string>

#include "config.h"
#include "../bot.h"

namespace FliwaBot {
  YAML::Node config::config_file;
  std::string config::license_footer;
  std::string config::cluster_name;
  std::string config::author_name;
  std::string config::author_id;
  bool config::command_status_send_dm;
  bool config::command_status_ephemeral;
  bool config::command_reload_ephemeral;
  std::string config::ping_command_name;
  std::string config::ping_command_description;
  std::string config::status_command_name;
  std::string config::status_command_description;
  std::string config::reload_command_name;
  std::string config::reload_command_description;
  std::string config::info_command_name;
  std::string config::info_command_description;

  void config::init(const char *file_path) {
    config_file = YAML::LoadFile(file_path);
    bot::log(FliwaCord::ll_info, "Configuration loaded from: " + std::string(file_path) + ".");

    license_footer = config_file["license-footer"].as<std::string>();
    cluster_name = config_file["cluster-name"].as<std::string>();
    author_name = config_file["author-name"].as<std::string>();
    author_id = config_file["author-id"].as<std::string>();
    command_status_send_dm = config_file["command-status-send-dm"].as<bool>();
    command_status_ephemeral = config_file["command-status-ephemeral"].as<bool>();
    command_reload_ephemeral = config_file["command-reload-ephemeral"].as<bool>();
    ping_command_name = config_file["ping-command-name"].as<std::string>();
    ping_command_description = config_file["ping-command-description"].as<std::string>();
    status_command_name = config_file["status-command-name"].as<std::string>();
    status_command_description = config_file["status-command-description"].as<std::string>();
    reload_command_name = config_file["reload-command-name"].as<std::string>();
    reload_command_description = config_file["reload-command-description"].as<std::string>();
    info_command_name = config_file["info-command-name"].as<std::string>();
    info_command_description = config_file["info-command-description"].as<std::string>();
  }
}