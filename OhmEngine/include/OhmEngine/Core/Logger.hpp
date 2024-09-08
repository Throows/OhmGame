#pragma once

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace OHE
{
    
    class Logger 
    {
        public:
            static void Init();

            inline static std::shared_ptr<spdlog::logger> &GetEngineLogger() { return s_EngineLogger; }
            inline static std::shared_ptr<spdlog::logger> &GetGameLogger() { return s_GameLogger; }

        private:
            static std::shared_ptr<spdlog::logger> s_EngineLogger;
            static std::shared_ptr<spdlog::logger> s_GameLogger;
    };

#define OHE_ENGINE_TRACE(...)    ::OHE::Logger::GetEngineLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::trace, __VA_ARGS__)
#define OHE_ENGINE_INFO(...)     ::OHE::Logger::GetEngineLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::info, __VA_ARGS__)
#define OHE_ENGINE_WARN(...)     ::OHE::Logger::GetEngineLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::warn, __VA_ARGS__)
#define OHE_ENGINE_ERROR(...)    ::OHE::Logger::GetEngineLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::err, __VA_ARGS__)
#define OHE_ENGINE_CRITICAL(...) ::OHE::Logger::GetEngineLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::critical, __VA_ARGS__)

#define OHE_GAME_TRACE(...)    ::OHE::Logger::GetGameLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::trace, __VA_ARGS__)
#define OHE_GAME_INFO(...)     ::OHE::Logger::GetGameLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::info, __VA_ARGS__)
#define OHE_GAME_WARN(...)     ::OHE::Logger::GetGameLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::warn, __VA_ARGS__)
#define OHE_GAME_ERROR(...)    ::OHE::Logger::GetGameLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::err, __VA_ARGS__)
#define OHE_GAME_CRITICAL(...) ::OHE::Logger::GetGameLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::critical, __VA_ARGS__)

} // namespace OHE
