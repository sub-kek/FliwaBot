//
// Created by sub on 5/24/24.
//

#include "builder.h"

namespace FliwaBot {
  FliwaCord::embed embed_builder::get_styled_embed() {
    FliwaCord::embed embed = FliwaCord::embed();

    embed.set_color(0x9f40ff);
    embed.set_footer(FliwaCord::embed_footer()
                         .set_text(dotenv::getenv("BASE_FOOTER")));

    return embed;
  }
}