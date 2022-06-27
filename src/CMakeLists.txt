# Copyright (c) 2022 Connor Mellon
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

file(GLOB SRCS **.cpp **.hpp)
if(WIN32)
  list(FILTER SRCS EXCLUDE REGEX ".*linux\\.cpp$")
else()
  list(FILTER SRCS EXCLUDE REGEX ".*win32\\.cpp$")
endif()

add_executable(micheal ${SRCS})
target_precompile_headers(micheal PRIVATE pch.hpp)

target_link_libraries(micheal
  PRIVATE
    project_settings
    spdlog
    dpp
  )

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRCS})
set_property(TARGET micheal PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
