#pragma once

#include "SGF/api.h"

#include <spdlog/spdlog.h>
#include <memory>

namespace SGF::Core
{
	class SGF_API Logger
	{
	public:
		static void Init();

		inline static spdlog::logger& GetCoreLogger() { return *s_CoreLogger.get(); }
		inline static spdlog::logger& GetAppLogger() { return *s_AppLogger.get(); }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_AppLogger;
	};
}

#define CORE_LOG_TRACE(...) SGF::Core::Logger::GetCoreLogger().trace(__VA_ARGS__)
#define CORE_LOG_INFO(...) SGF::Core::Logger::GetCoreLogger().info(__VA_ARGS__)
#define CORE_LOG_WARNING(...) SGF::Core::Logger::GetCoreLogger().warn(__VA_ARGS__)
#define CORE_LOG_ERROR(...) SGF::Core::Logger::GetCoreLogger().error(__VA_ARGS__)
#define CORE_LOG_CRITICAL(...) SGF::Core::Logger::GetCoreLogger().critical(__VA_ARGS__)

#define APP_LOG_TRACE(...) SGF::Core::Logger::GetAppLogger().trace(__VA_ARGS__)
#define APP_LOG_INFO(...) SGF::Core::Logger::GetAppLogger().info(__VA_ARGS__)
#define APP_LOG_WARNING(...) SGF::Core::Logger::GetAppLogger().warn(__VA_ARGS__)
#define APP_LOG_ERROR(...) SGF::Core::Logger::GetAppLogger().error(__VA_ARGS__)
#define APP_LOG_CRITICAL(...) SGF::Core::Logger::GetAppLogger().critical(__VA_ARGS__)