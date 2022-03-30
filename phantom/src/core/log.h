#pragma once
#include <fmt/format.h>
#include <fmt/chrono.h>
#include <fmt/color.h>

#define TIMESTAP_FORMAT "[{:%Y-%m-%d %H:%M:%S}] "

PH_NAMESPACE_BEGIN

class Log
{
public:

    template <typename... Args>
    static void core_fatal(std::string_view format, const Args&... args) {
        get()->fatal("core", format, args...);
    }

    template <typename... Args>
    static void core_error(std::string_view format, const Args&... args) {
        get()->error("core", format, args...);
    }
    
    template <typename... Args>
    static void core_warning(std::string_view format, const Args&... args) {
        get()->warning("core", format, args...);
    }
    
    template <typename... Args>
    static void core_info(std::string_view format, const Args&... args) {
        get()->info("core", format, args...);
    }
    
    template <typename... Args>
    static void core_trace(std::string_view format, const Args&... args) {
        get()->trace("core", format, args...);
    }

    template <typename... Args>
    static void app_fatal(std::string_view format, const Args&... args) {
        get()->fatal("app", format, args...);
    }

    template <typename... Args>
    static void app_error(std::string_view format, const Args&... args) {
        get()->error("app", format, args...);
    }
    
    template <typename... Args>
    static void app_warning(std::string_view format, const Args&... args) {
        get()->warning("app", format, args...);
    }
    
    template <typename... Args>
    static void app_info(std::string_view format, const Args&... args) {
        get()->info("app", format, args...);
    }
    
    template <typename... Args>
    static void app_trace(std::string_view format, const Args&... args) {
        get()->trace("app", format, args...);
    }
    
    static Log* get() {
        static Log* instance = new Log();

        return instance;
    }

    ~Log() = default;
private:
    Log() = default;

    template <typename... Args>
    inline void fatal(const char* level, std::string_view format, const Args&... args) {
        auto time = std::chrono::system_clock::now();
        fmt::print(fmt::emphasis::bold | fmt::fg(fmt::color::red), fmt::format(TIMESTAP_FORMAT "[{}] [fatal]: {}\n", level, fmt::format(format, args...)));
    }

    template <typename... Args>
    inline void error(const char* level, std::string_view format, const Args&... args) {
        auto time = std::chrono::system_clock::now();
        fmt::print(fmt::emphasis::bold | fmt::fg(fmt::color::orange), fmt::format(TIMESTAP_FORMAT "[{}] [error]: {}\n", level, fmt::format(format, args...)));
    }

    template <typename... Args>
    inline void warning(const char* level, std::string_view format, const Args&... args) {
        auto time = std::chrono::system_clock::now();
        fmt::print(fmt::emphasis::bold | fmt::fg(fmt::color::yellow), fmt::format(TIMESTAP_FORMAT "[{}] [warning]: {}\n", level, fmt::format(format, args...)));
    }

    template <typename... Args>
    inline void info(const char* level, std::string_view format, const Args&... args) {
        auto time = std::chrono::system_clock::now();
        fmt::print(fmt::emphasis::bold | fmt::fg(fmt::color::lime_green), fmt::format(TIMESTAP_FORMAT "[{}] [info]: {}\n", time, level, fmt::format(format, args...)));
    }

    template <typename... Args>
    inline void trace(const char* level, std::string_view format, const Args&... args) {
        auto time = std::chrono::system_clock::now();
        fmt::print(fmt::emphasis::bold | fmt::fg(fmt::color::sky_blue), fmt::format(TIMESTAP_FORMAT "[{}] [trace]: {}\n", time, level, fmt::format(format, args...)));
    }
};

PH_NAMESPACE_END