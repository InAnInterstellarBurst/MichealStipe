// Copyright (c) 2022 Connor Mellon
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

using LogHandle = std::shared_ptr<spdlog::logger>;

class Logger
{
public:
	static void make_logger();
	static void on_log(const dpp::log_t& e);
	static LogHandle get() noexcept;
private:
	static LogHandle m_hdl;
};
