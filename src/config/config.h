#pragma once

#include <yaml-cpp/yaml.h>
#include <string>

namespace FliwaBot {
  class config {
  private:
    static YAML::Node config_file;

  public:
    static void init(const char *file_path);

    static std::string license_footer;
    static std::string cluster_name;
    static std::string author_name;
  };
}