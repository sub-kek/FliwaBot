#include "utility.h"

#include <fstream>
#include <iostream>
#include <regex>

namespace FliwaBot {
  void dotenv::init(const char *filename) {
    dotenv::do_init(OptionsNone, filename);
  }

  void dotenv::init(int flags, const char *filename) {
    dotenv::do_init(flags, filename);
  }

  std::string dotenv::getenv(const char *name, const std::string &def) {
    const char *str = std::getenv(name);
    return str ? std::string(str) : def;
  }

  size_t dotenv::find_var_start(const std::string &str, size_t pos, std::string &start_tag) {
    size_t p1 = str.find('$', pos);
    size_t p2 = str.find("${", pos);
    size_t pos_var = (std::min)(p1, p2);
    if (pos_var != std::string::npos) start_tag = (pos_var == p2) ? "${" : "$";
    return pos_var;
  }

  size_t dotenv::find_var_end(const std::string &str, size_t pos, const std::string &start_tag) {
    char end_tag = (start_tag == "${") ? '}' : ' ';
    size_t pos_end = str.find(end_tag, pos);
    if (pos_end == std::string::npos && end_tag == ' ') pos_end = str.length();
    return pos_end;
  }

  void dotenv::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) { return !std::isspace(c); }));
  }

  void dotenv::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int c) { return !std::isspace(c); }).base(), s.end());
  }

  void dotenv::trim(std::string &s) {
    ltrim(s);
    rtrim(s);
  }

  std::string dotenv::trim_copy(std::string s) {
    trim(s);
    return s;
  }

  std::pair<std::string, bool> dotenv::resolve_vars(size_t iline, const std::string &str) {
    std::string resolved;
    size_t pos = 0;
    size_t pre_pos = pos;
    size_t nvar = 0;
    bool finished = false;
    while (!finished) {
      std::string start_tag;
      pos = find_var_start(str, pos, start_tag);
      if (pos != std::string::npos) {
        nvar++;
        size_t pos_start = pos;
        size_t lstart = start_tag.length();
        size_t lend = (lstart > 1) ? 1 : 0;
        resolved += str.substr(pre_pos, pos - pre_pos);
        pos = find_var_end(str, pos, start_tag);
        if (pos != std::string::npos) {
          std::string var = str.substr(pos_start, pos - pos_start + 1);
          std::string env_var = var.substr(lstart, var.length() - lstart - lend);
          rtrim(env_var);
          if (const char *env_str = std::getenv(env_var.c_str())) {
            resolved += env_str;
            nvar--;
          } else {
            std::cout << "dotenv: Variable " << var << " is not defined on line " << iline << std::endl;
          }
          pre_pos = pos + lend;
        }
      } else {
        finished = true;
      }
    }
    if (pre_pos < str.length()) {
      resolved += str.substr(pre_pos);
    }
    return std::make_pair(resolved, (nvar == 0));
  }

  void dotenv::do_init(int flags, const char *filename) {
    std::ifstream file;
    std::string line;
    file.open(filename);
    if (file) {
      unsigned int i = 1;
      while (getline(file, line)) {
        const auto pos = line.find("=");
        if (pos == std::string::npos) {
          std::cout << "dotenv: Ignoring ill-formed assignment on line "
                    << i << ": '" << line << "'" << std::endl;
        } else {
          auto name = trim_copy(line.substr(0, pos));
          auto line_stripped = strip_quotes(trim_copy(line.substr(pos + 1)));
          auto p = resolve_vars(i, line_stripped);
          bool ok = p.second;
          if (!ok) {
            std::cout << "dotenv: Ignoring ill-formed assignment on line "
                      << i << ": '" << line << "'" << std::endl;
          } else {
            const auto &val = p.first;
            setenv(name.c_str(), val.c_str(), ~flags & dotenv::Preserve);
          }
        }
        ++i;
      }
    }
  }

  std::string dotenv::strip_quotes(const std::string &str) {
    const std::size_t len = str.length();
    if (len < 2)
      return str;
    const char first = str[0];
    const char last = str[len - 1];
    if (first == last && ('"' == first || '\'' == first))
      return str.substr(1, len - 2);
    return str;
  }

  std::string formatter::format(std::string str, const std::initializer_list<std::string>& replace) {
    int i = 0;
    for (const auto& repl : replace) {
      std::string pattern = "\\{" + std::to_string(i) + "\\}";
      str = std::regex_replace(str, std::regex(pattern), repl);
      i++;
    }
    return str;
  }

  void thread_locker::wait() {
    std::unique_lock<std::mutex> lock(mtx);
    lck.wait(lock, [&] { return completed == true; });
  }

  void thread_locker::complete() {
    std::lock_guard<std::mutex> lock(mtx);
    completed = true;
    lck.notify_all();
  }
}