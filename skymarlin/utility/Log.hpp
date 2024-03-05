/*
 * MIT License
 *
 * Copyright (c) 2024 skymarlin
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/ostream_sink.h>

#include <iostream>

namespace skymarlin::utility
{
#define SKYMARLIN_LOG_INFO(format, ...) \
    spdlog::info(format __VA_OPT__(,) __VA_ARGS__)

#define SKYMARLIN_LOG_ERROR(format, ...) \
    spdlog::error(format __VA_OPT__(,) __VA_ARGS__)

#define SKYMARLIN_LOG_WARN(format, ...) \
    spdlog::warn(format __VA_OPT__(,) __VA_ARGS__)

#define SKYMARLIN_LOG_CRITICAL(format, ...) \
    spdlog::critical(format __VA_OPT__(,) __VA_ARGS__)

#define SKYMARLIN_LOG_DEBUG(format, ...) \
    spdlog::debug(format __VA_OPT__(,) __VA_ARGS__)


class Log final
{
public:
    static void Redirect(std::ostream& os)
    {
        const auto ostream_sink = std::make_shared<spdlog::sinks::ostream_sink_mt>(os);
        spdlog::default_logger()->sinks().clear();
        spdlog::default_logger()->sinks().push_back(ostream_sink);
    }
};
}