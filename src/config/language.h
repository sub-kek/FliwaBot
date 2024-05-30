#pragma once

#include <yaml-cpp/yaml.h>

namespace FliwaBot {
    class language {
    private:
        static YAML::Node language_file;

    public:
        static void init(const char *file_path);

        static std::string command_status_embed_description;
        static std::string command_status_embed_title;
        static std::string command_status_reply_text;
        static std::string command_reload_successfully;
        static std::string command_reload_no_perms;
        static std::string command_ping_embed_description_checking;
        static std::string command_ping_embed_description;
        static std::string info_command_embed_title;
        static std::string info_command_embed_description;
        static std::string info_command_embed_field_build_name;
        static std::string info_command_embed_field_build_value;
        static std::string info_command_embed_field_developer_name;
        static std::string info_command_embed_field_developer_value;
    };
}