// Copyright (c) 2022 Connor Mellon
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "pch.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>

LogHandle Logger::m_hdl = nullptr;

void Logger::make_logger()
{
	auto stdoutSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	stdoutSink->set_pattern("[%l] %^%n%$: %v");

	auto l = std::make_shared<spdlog::logger>("Micheal", stdoutSink);
	spdlog::register_logger(l);
	l->flush_on(spdlog::level::trace);
	l->set_level(spdlog::level::trace);
	m_hdl = l;
}

void Logger::on_log(const dpp::log_t &e)
{
	switch(e.severity) {
	case dpp::loglevel::ll_critical:
		m_hdl->critical(e.message);
		break;
	case dpp::loglevel::ll_error:
		m_hdl->error(e.message);
		break;
	case dpp::loglevel::ll_warning:
		m_hdl->warn(e.message);
		break;
	case dpp::loglevel::ll_info:
		m_hdl->info(e.message);
		break;
	default:
		m_hdl->trace(e.message);
		break;
	}
}

LogHandle Logger::get() noexcept
{
	return m_hdl;
}
