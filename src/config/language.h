#pragma once

#include <yaml-cpp/yaml.h>
#include <string>

namespace FliwaBot {
  class language {
  private:
    static YAML::Node language_file;

  public:
    static void init(const char *file_path);

    static std::string command_status_embed_description;
  };
}