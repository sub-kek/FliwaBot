//
// Created by sub on 5/24/24.
//

#pragma once

#include <FliwaCord/message.h>
#include <FliwaCord/colors.h>

#include "utility.h"

namespace FliwaBot {
  class embed_builder {
  public:
    embed_builder() = delete;
    ~embed_builder() = delete;

    static FliwaCord::embed get_styled_embed();
  };
}