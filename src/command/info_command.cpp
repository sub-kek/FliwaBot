#include "info_command.h"

#include "../config/config.h"
#include "../config/language.h"
#include "../builder.h"
#include "../utility.h"

namespace FliwaBot {
  std::string info_command::get_name() {
    return config::info_command_name;
  }

  std::string info_command::get_description() {
    return config::info_command_description;
  }

  void info_command::execute(const FliwaCord::slashcommand_t &event) {
    FliwaCord::embed embed = embed_builder::get_styled_embed()
        .set_title(language::info_command_embed_title)
        .set_description(language::info_command_embed_description)
        .add_field(
            language::info_command_embed_field_build_name,
            formatter::format(language::info_command_embed_field_build_value, {dotenv::getenv("VERSION")}),
            true
        )
        .add_field(
            language::info_command_embed_field_developer_name,
            formatter::format(language::info_command_embed_field_developer_value, {config::author_name}),
            true
        );
    event.reply(embed);
  }
}