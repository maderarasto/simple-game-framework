#include "Logger.h"

#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

using namespace SGF::Core;

std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
std::shared_ptr<spdlog::logger> Logger::s_AppLogger;


void Logger::Init()
{
	spdlog::set_level(spdlog::level::trace);
	spdlog::set_pattern("%^[%T] [%n]\t%v%$");

	s_CoreLogger = spdlog::stdout_color_mt("SGF");
	s_AppLogger = spdlog::stdout_color_mt("App");
}