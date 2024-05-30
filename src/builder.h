#pragma once

namespace FliwaBot {
    class embed_builder {
    public:
        embed_builder() = delete;

        ~embed_builder() = delete;

        static FliwaCord::embed get_styled_embed();
    };

    class message_builder {
    public:
        message_builder() = delete;

        ~message_builder() = delete;
    };
}