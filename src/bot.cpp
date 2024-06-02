#include "bot.h"
#include "event/fliwa_event.h"
#include "command/command.h"
#include "form/form.h"
#include "button/button.h"
#include "utility.h"

namespace FliwaBot {
    FliwaCord::cluster *bot::core;
    std::string bot::start_data::token;
    FliwaCord::intents bot::start_data::intents;

    bool bot::start() {
        core->start(FliwaCord::st_wait);
        return true;
    }

    void bot::register_events() {
        core->on_log(logger);
        core->on_slashcommand(event::on_slashcommand);
        core->on_form_submit(event::on_form_submit);
        core->on_button_click(event::on_button_click);
        core->on_ready(event::on_ready);
    }

    void bot::register_slashcommands() {
        command::register_commands();

//        for (const auto &cmd: core->global_commands_get_sync()) {
//            auto *locker = new thread_locker;
//
//            core->global_command_delete(cmd.second.id, [&](const FliwaCord::confirmation_callback_t &) {
//                log(FliwaCord::ll_info,
//                    formatter::format("Удалена команда {0} - {1}",
//                                      {cmd.second.name, cmd.second.description}));
//
//                locker->complete();
//            });
//
//            locker->wait();
//        }

        for (auto &cmd: command::commands) {
            core->global_command_create(FliwaCord::slashcommand(cmd->get_name(), cmd->get_description(), core->me.id),
                                        [&](const FliwaCord::confirmation_callback_t &) {
                                            core->log(FliwaCord::ll_info,
                                                      formatter::format("Зарегистрирована команда {0} - {1}",
                                                                        {cmd->get_name(), cmd->get_description()}));
                                        });
        }
    }

    void bot::register_forms() {
        form::register_forms();
    }

    void bot::register_buttons() {
        button::register_buttons();
    }

    void bot::init() {
        core = new FliwaCord::cluster(start_data::token, start_data::intents);
    }

    void bot::logger(const FliwaCord::log_t &event) {
        std::cout
                << "[" << FliwaCord::utility::current_date_time() << " " << FliwaCord::utility::loglevel(event.severity)
                << "]"
                << ": " << event.message << "\n";
    }

    void bot::log(const FliwaCord::loglevel &severity, const std::string &message) {
        std::cout
                << "[" << FliwaCord::utility::current_date_time() << " " << FliwaCord::utility::loglevel(severity)
                << "]"
                << ": " << message << "\n";
    }
}