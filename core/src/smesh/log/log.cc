#include "log.h"
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace smesh
{
    static std::shared_ptr<spdlog::logger> core_logger;
    static std::shared_ptr<spdlog::logger> client_logger;

    void Log::Init()
    {
        spdlog::set_pattern("%^[%T] %n: %v%$");
        core_logger = spdlog::stdout_color_mt("SMesh");
        client_logger = spdlog::stdout_color_mt("App");
        core_logger->set_level(spdlog::level::trace);
        client_logger->set_level(spdlog::level::trace);
    }
    
    std::shared_ptr<spdlog::logger> Log::GetClientLogger()
    {
        return client_logger;
    }

    std::shared_ptr<spdlog::logger> Log::GetCoreLogger()
    {
        return core_logger;
    }
}