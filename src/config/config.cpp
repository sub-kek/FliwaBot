#include "config.h"

#include "../bot.h"

namespace FliwaBot {
  YAML::Node config::config_file;

  std::string config::license_footer;
  std::string config::cluster_name;
  std::string config::author_name;

  void config::init(const char *file_path) {
    config_file = YAML::LoadFile(file_path);
    bot::core->log(FliwaCord::ll_info, "Configuration loaded from: " + std::string(file_path) + ".");

    license_footer = config_file["license-footer"].as<std::string>();
    cluster_name = config_file["cluster-name"].as<std::string>();
    author_name = config_file["author-name"].as<std::string>();
  }
}