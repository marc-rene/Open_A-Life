#include "Log.h"


namespace A_LIFE
{
	std::shared_ptr <spdlog::logger> A_LIFE_Log::Init()
	{
		return A_LIFE_Log::Init("A-LIFE");
	}

	std::shared_ptr <spdlog::logger> A_LIFE_Log::Init(const char* LoggerName)
	{
		try
		{
			return spdlog::stdout_color_mt(LoggerName);
		}
		catch (const spdlog::spdlog_ex&) // Logger probably already exists
		{
			return spdlog::get(LoggerName);
		}
	}

	std::shared_ptr<spdlog::logger> A_LIFE_Log::GetLogger()
	{
		return A_LIFE_Log::GetLogger("A-LIFE");
	}

	std::shared_ptr<spdlog::logger> A_LIFE_Log::GetLogger(const char* LoggerName)
	{
		// Use Init instead because if the logger doesn't exist we'll make one..very sketch
		if (spdlog::get(LoggerName) == nullptr)
		{
			A_LIFE_Log::Init(LoggerName);
		}

		return spdlog::get(LoggerName);
	}
}
