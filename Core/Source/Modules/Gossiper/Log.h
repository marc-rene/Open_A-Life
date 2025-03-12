#pragma once
#include "Core/Core.h"  
/*
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/stopwatch.h"
*/
#include "Core/Type_Definitions.hpp"
#include <memory>


namespace Core
{
	class Log
	{
	public:
		static mint Init();

		/*inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
		{
			return CoreLogger;
		}

		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger()
		{
			return EngineLogger;
		}


		static inline std::shared_ptr<spdlog::logger> CoreLogger;
		static inline std::shared_ptr<spdlog::logger> EngineLogger;
	*/
	};
}





#define INFOc(...) Core::Log::GetCoreLogger()->debug(__VA_ARGS__)
#define SUCCESSc(...) Core::Log::GetCoreLogger()->info(__VA_ARGS__)
#define WARNc(...) Core::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ERRORc(...) Core::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define SUCCESS_msg "GREAT SUCESS"
#define FAILURE_msg "Oh Wawaweewa..."
#define TIMER_START spdlog::stopwatch sw
#define TIMER_ELAPSEDc(...) Core::Log::GetCoreLogger()->debug(__VA_ARGS__, sw)


#define INFOe(...) ::Core::Log::GetEngineLogger()->debug(__VA_ARGS__)
#define SUCCESSe(...) ::Core::Log::GetEngineLogger()->info(__VA_ARGS__)
#define WARNe(...) ::Core::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define ERRORe(...) ::Core::Log::GetEngineLogger()->error(__VA_ARGS__)