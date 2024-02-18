#pragma once
#include "smesh/core.h"
#include <memory>
#include <spdlog/logger.h>

namespace smesh
{
    class SMESH_API Log
    {
      public:
        void static Init();

#ifdef SMESH_BUILD_LIBRARY
        static std::shared_ptr<spdlog::logger> GetCoreLogger();
#endif
        static std::shared_ptr<spdlog::logger> GetClientLogger();
    };
} // namespace smesh

#ifdef SMESH_BUILD_LIBRARY
#define SMESH_TRACE(...) ::smesh::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SMESH_INFO(...) ::smesh::Log::GetCoreLogger()->info(__VA_ARGS__)
#define SMESH_WARN(...) ::smesh::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SMESH_ERROR(...) ::smesh::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SMESH_FATAL(...) ::smesh::Log::GetCoreLogger()->critical(__VA_ARGS__)
#else
#define SMESH_TRACE(...) ::smesh::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SMESH_INFO(...) ::smesh::Log::GetClientLogger()->info(__VA_ARGS__)
#define SMESH_WARN(...) ::smesh::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SMESH_ERROR(...) ::smesh::Log::GetClientLogger()->error(__VA_ARGS__)
#define SMESH_FATAL(...) ::smesh::Log::GetClientLogger()->critical(__VA_ARGS__)
#endif