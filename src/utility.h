//
// Created by sub on 5/24/24.
//

#pragma once

#include <string>
#include <fstream>
#include <iostream>

namespace FliwaBot {
  class dotenv {
  public:
    dotenv() = delete;

    ~dotenv() = delete;

    static const unsigned char Preserve = 1 << 0;
    static const int OptionsNone = 0;

    static void init(const char *filename = ".env");

    static void init(int flags, const char *filename = ".env");

    static std::string getenv(const char *name, const std::string &def = "");

  private:
    static void do_init(int flags, const char *filename);

    static std::string strip_quotes(const std::string &str);

    static std::pair<std::string, bool> resolve_vars(size_t iline, const std::string &str);

    static void ltrim(std::string &s);

    static void rtrim(std::string &s);

    static void trim(std::string &s);

    static std::string trim_copy(std::string s);

    static size_t find_var_start(const std::string &str, size_t pos, std::string &start_tag);

    static size_t find_var_end(const std::string &str, size_t pos, const std::string &start_tag);
  };
}