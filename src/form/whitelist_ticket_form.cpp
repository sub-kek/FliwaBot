#include <regex>

#include "whitelist_ticket_form.h"
#include "../bot.h"
#include "../builder.h"
#include "../utility.h"
#include "../config.h"

namespace FliwaBot {
    std::string whitelist_ticket_form::get_id() {
        return "whitelist_ticket_form";
    }

    FliwaCord::interaction_modal_response whitelist_ticket_form::get_form() {
        return FliwaCord::interaction_modal_response()
                .set_title("Заявка на сервер")
                .add_component(
                        FliwaCord::component()
                                .set_label("Ваш игровой ник")
                                .set_id("nickname")
                                .set_placeholder("Steve")
                                .set_type(FliwaCord::cot_text)
                                .set_text_style(FliwaCord::text_short)
                                .set_max_length(16)
                                .set_min_length(3)
                                .set_required(true))
                .add_row()
                .add_component(
                        FliwaCord::component()
                                .set_label("Ваш возвраст")
                                .set_id("age")
                                .set_placeholder("15")
                                .set_type(FliwaCord::cot_text)
                                .set_text_style(FliwaCord::text_short)
                                .set_max_length(2)
                                .set_min_length(1)
                                .set_required(true))
                .set_custom_id(get_id());
    }

    void whitelist_ticket_form::submit(const FliwaCord::form_submit_t &event) {
        std::string nickname = std::get<std::string>(event.components[0].components[0].value);
        std::string age_str = std::regex_replace(std::get<std::string>(event.components[1].components[0].value),
                                                 std::regex("[^0-9]+"), "");

        std::string channel_name = std::regex_replace(event.command.get_issuing_user().username,
                                                      std::regex("#"), "\\#");

        bool can_create_ticket = true;

        for (const auto &channel_pair: bot::core->channels_get_sync(config::guild_id)) {
            const auto &channel = channel_pair.second;
            if (channel.parent_id.str() == config::whitelist_tickets_category && channel.name == channel_name) {
                can_create_ticket = false;
                break;
            }
        }

        if (!can_create_ticket) {
            FliwaCord::message failed_message = FliwaCord::message()
                    .add_embed(
                            embed_builder::get_styled_embed()
                                    .set_title("Ошибка")
                                    .set_description("Тикет уже существует"))
                    .set_flags(FliwaCord::m_ephemeral);

            event.reply(failed_message);

            return;
        }

        FliwaCord::channel channel = FliwaCord::channel()
                .set_name(channel_name)
                .set_parent_id(config::whitelist_tickets_category)
                .set_guild_id(config::guild_id);

        auto *locker = new thread_locker;

        std::string channel_mention;

        bot::core->channel_create(channel, [&](const FliwaCord::confirmation_callback_t &callback) {
            auto created = callback.get<FliwaCord::channel>();

            channel_mention = created.get_mention();

            FliwaCord::message ticket_message = FliwaCord::message()
                    .add_embed(
                            embed_builder::get_styled_embed()
                                    .set_title("Заявка в вайтлист")
                                    .set_description(
                                            formatter::format(
                                                    "Никнейм: {0}\n"
                                                    "Возвраст: {1}",
                                                    {nickname, age_str}))
                                    .add_field("Подающий", event.command.get_issuing_user().get_mention()))
                    .set_channel_id(created.id);

            bot::core->message_create(ticket_message);

            locker->complete();
        });

        locker->wait();

        FliwaCord::message message = FliwaCord::message()
                .add_embed(
                        embed_builder::get_styled_embed()
                                .set_title("Тикет создан")
                                .set_description(
                                        formatter::format(
                                                "Вы можете посмотреть его здесь {0}",
                                                {channel_mention})
                                )
                )
                .set_flags(FliwaCord::m_ephemeral);

        event.reply(message);
    }
}