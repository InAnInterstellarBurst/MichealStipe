// Copyright (c) 2022 Connor Mellon
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "pch.hpp"
#include "priv.tok"

const std::unordered_map<std::string, std::string> SomeYolkes
{
	{ "animal_Thom", "https://ichef.bbci.co.uk/news/1024/cpsprodpb/ECAD/production/_96398506_31f5870a-bf0a-43ee-9e5c-7db651522d52.jpg" },
	{ "animal_Johnny", "https://preview.redd.it/monn9thhsr911.jpg?auto=webp&s=22b05ee439d82830991f3ce35fd19645e55520c5" },
	{ "animal_Ed", "https://preview.redd.it/7gc3cii0phk21.png?auto=webp&s=de932dfb45efda8bfa1612dd21f9225a1e5bdff3" },
	{ "animal_Colin", "http://31.media.tumblr.com/f5ebad785c9b8a3cf53a45df3f7ef62c/tumblr_mlxbo26JdQ1qgqe6xo1_400.gif" },
	{ "animal_Phil", "https://m.media-amazon.com/images/I/81Ab9tsZsQS._AC_SL1500_.jpg" }
};

int main()
{
	Logger::make_logger();
	dpp::cluster bot(sToken);
	bot.on_log(Logger::on_log);

	bot.on_slashcommand([](const dpp::slashcommand_t& evt) {
		if(evt.command.get_command_name() == "ping") {
			evt.reply("Fuck you");
		} else if(evt.command.get_command_name() == "blep") {
			auto animal = std::get<std::string>(evt.get_parameter("animal"));
			dpp::message resp;
			dpp::embed e;
			e.set_image(SomeYolkes.at(animal));
			resp.add_embed(e);
			evt.reply(resp);
		}
	});

	bot.on_ready([&bot](const dpp::ready_t& evt) {
		if(dpp::run_once<struct register_bot_commands>()) {
			bot.global_command_create(dpp::slashcommand("ping", "ping pong?", bot.me.id));

			dpp::slashcommand blep("blep", "Get a cute animal", bot.me.id);
			blep.add_option(dpp::command_option(dpp::co_string, "animal", "Type of animal", true)
				.add_choice(dpp::command_option_choice("Thom", std::string("animal_Thom")))
				.add_choice(dpp::command_option_choice("Johnny", std::string("animal_Johnny")))
				.add_choice(dpp::command_option_choice("Ed", std::string("animal_Ed")))
				.add_choice(dpp::command_option_choice("Colin", std::string("animal_Colin")))
				.add_choice(dpp::command_option_choice("Phil", std::string("animal_Phil")))
				);
			bot.global_command_create(blep);
		}
	});

	bot.start(false);
	return EXIT_SUCCESS;
}
