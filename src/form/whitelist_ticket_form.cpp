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
                                .set_label("Ваш игровой ник.")
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
                                .set_label("Ваш возвраст.")
                                .set_id("age")
                                .set_placeholder("15")
                                .set_type(FliwaCord::cot_text)
                                .set_text_style(FliwaCord::text_short)
                                .set_max_length(2)
                                .set_min_length(1)
                                .set_required(true))
                .add_row()
                .add_component(
                        FliwaCord::component()
                                .set_label("Откуда узнали о сервере?")
                                .set_id("where_known")
                                .set_placeholder("Пример: От друга <дискорд друга>")
                                .set_type(FliwaCord::cot_text)
                                .set_text_style(FliwaCord::text_paragraph)
                                .set_max_length(128)
                                .set_min_length(8)
                                .set_required(true))
                .add_row()
                .add_component(
                        FliwaCord::component()
                                .set_label("Изучили ли вы правила сервера?")
                                .set_id("studied_rules")
                                .set_placeholder("Пример: Конечно")
                                .set_type(FliwaCord::cot_text)
                                .set_text_style(FliwaCord::text_short)
                                .set_min_length(2)
                                .set_max_length(16)
                                .set_required(true))
                .add_row()
                .add_component(
                        FliwaCord::component()
                                .set_label("Если увидите нарушение со стороны игрока")
                                .set_id("rules_breaking")
                                .set_placeholder("Пример: Пожалуюсь администрации")
                                .set_type(FliwaCord::cot_text)
                                .set_text_style(FliwaCord::text_paragraph)
                                .set_max_length(128)
                                .set_min_length(8)
                                .set_required(true))
                .set_custom_id(get_id());
    }

    void whitelist_ticket_form::submit(const FliwaCord::form_submit_t &event) {
        std::string nickname = std::get<std::string>(event.components[0].components[0].value);
        std::string age_str = std::get<std::string>(event.components[1].components[0].value);
        std::string where_known = std::get<std::string>(event.components[2].components[0].value);
        std::string studied_rules = std::get<std::string>(event.components[3].components[0].value);
        std::string rule_breaking = std::get<std::string>(event.components[4].components[0].value);

        std::string channel_name = formatter::format("заявка-{0}", {event.command.get_issuing_user().username});

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

            bot::core->channel_edit_permissions(created.id, event.command.get_issuing_user().id,
                                                FliwaCord::p_view_channel, 0x0, true);

            channel_mention = created.get_mention();

            FliwaCord::message ticket_message = FliwaCord::message()
                    .add_embed(
                            embed_builder::get_styled_embed()
                                    .set_title("Заявка в вайтлист")
                                    .add_field("Никнейм", nickname)
                                    .add_field("Возвраст", age_str)
                                    .add_field("Откуда узнали о сервере", where_known)
                                    .add_field("Изучили ли вы правила сервера", studied_rules)
                                    .add_field("Если увидите нарушение со стороны игрока?", rule_breaking)
                                    .add_field("Подающий", event.command.get_issuing_user().get_mention()))
                    .set_channel_id(created.id)
                    .add_component(
                            FliwaCord::component()
                                    .set_type(FliwaCord::cot_action_row)
                                    .add_component(
                                            FliwaCord::component()
                                                    .set_type(FliwaCord::cot_button)
                                                    .set_emoji("🔒")// :lock:
                                                    .set_label("Закрыть")
                                                    .set_id("ticket_close_button")
                                                    .set_style(FliwaCord::cos_secondary))
                    );

            bot::core->message_create(ticket_message);

            locker->complete();
        });

        locker->wait();

        FliwaCord::message
                message = FliwaCord::message()
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