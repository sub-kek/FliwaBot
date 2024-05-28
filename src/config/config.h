#pragma once

#include <yaml-cpp/yaml.h>

namespace FliwaBot {
  class config {
  private:
    static YAML::Node language_file;

  public:
    static void init(const char *file_path);

    static std::string license_footer;
    static std::string cluster_name;
    static std::string author_name;
    static std::string author_id;
    static bool command_status_send_dm;
    static bool command_status_ephemeral;
    static bool command_reload_ephemeral;
  };
}