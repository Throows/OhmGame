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

#define OHE_ENGINE_TRACE(...)    ::OHE::Logger::GetEngineLogger()->trace(__VA_ARGS__)
#define OHE_ENGINE_INFO(...)     ::OHE::Logger::GetEngineLogger()->info(__VA_ARGS__)
#define OHE_ENGINE_WARN(...)     ::OHE::Logger::GetEngineLogger()->warn(__VA_ARGS__)
#define OHE_ENGINE_ERROR(...)    ::OHE::Logger::GetEngineLogger()->error(__VA_ARGS__)
#define OHE_ENGINE_CRITICAL(...) ::OHE::Logger::GetEngineLogger()->critical(__VA_ARGS__)

#define OHE_GAME_TRACE(...)    ::OHE::Logger::GetGameLogger()->trace(__VA_ARGS__)
#define OHE_GAME_INFO(...)     ::OHE::Logger::GetGameLogger()->info(__VA_ARGS__)
#define OHE_GAME_WARN(...)     ::OHE::Logger::GetGameLogger()->warn(__VA_ARGS__)
#define OHE_GAME_ERROR(...)    ::OHE::Logger::GetGameLogger()->error(__VA_ARGS__)
#define OHE_GAME_CRITICAL(...) ::OHE::Logger::GetGameLogger()->critical(__VA_ARGS__)

} // namespace OHE
