# Copyright (c) 2022 Connor Mellon
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.18)
project(micheal_stipe)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()


include(cmake/tools.cmake)
include(cmake/pvt_is.cmake)
include(cmake/warnings.cmake)

add_library(project_settings INTERFACE)
enable_sanitisers(project_settings)
set_project_warnings(project_settings)
target_compile_features(project_settings INTERFACE cxx_std_20)
target_compile_definitions(project_settings INTERFACE DEBUG=$<CONFIG:DEBUG> _CRT_SECURE_NO_WARNINGS)


add_subdirectory(dep/dpp)
add_subdirectory(dep/spdlog)

add_subdirectory(src)
enable_ipo(stipe)
