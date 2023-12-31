#include <OhmEngine/Core/Logger.hpp>

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace OHE 
{
    std::shared_ptr<spdlog::logger> Logger::s_EngineLogger;
    std::shared_ptr<spdlog::logger> Logger::s_GameLogger;

    void Logger::Init()
    {

        std::vector<spdlog::sink_ptr> logSinks;
        // Sinks 
        auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("OhmEngine.log", true);
        auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        // Set the pattern
        fileSink->set_pattern("%^[%L](%T) %n in %s:%# -> %v%$");
        consoleSink->set_pattern("%^[%L](%T) %n: %v%$");

        fileSink->set_level(spdlog::level::info);

        logSinks.push_back(consoleSink);
        logSinks.push_back(fileSink);

        s_EngineLogger = std::make_shared<spdlog::logger>("ENGI", begin(logSinks), end(logSinks));
        s_EngineLogger->set_level(spdlog::level::trace);
        s_EngineLogger->flush_on(spdlog::level::trace);

        s_GameLogger = std::make_shared<spdlog::logger>("GAME", begin(logSinks), end(logSinks));
        s_GameLogger->set_level(spdlog::level::trace);
        s_GameLogger->flush_on(spdlog::level::trace);
    }
}