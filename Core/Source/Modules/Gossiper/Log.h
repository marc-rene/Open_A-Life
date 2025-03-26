#pragma once
#include "Core/Type_Definitions.hpp"

#include <memory>
#include "spdlog/spdlog.h"

/*
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/stopwatch.h"
*/

namespace A_LIFE
{
	class A_LIFE_Log
	{
	public:
		static inline std::shared_ptr<spdlog::sinks::stdout_sink_st> CORE_LOGGER_SINK;
		static spdlog::logger CORE_LOGGER;
		//inline static std::shared_ptr<spdlog::logger>& GetLogger()	{ return CORE_LOGGER; }
		static void Init();

	};
}





#define INFOc(...) spdlog::get("A-LIFE")->info(__VA_ARGS__)
//#define INFOc(...) spdlog::info(__VA_ARGS__)
//#define INFOc(...) A_LIFE::A_LIFE_Log::GetLogger()->info(__VA_ARGS__)
#define SUCCESSc(...) Core::Log::GetCoreLogger()->info(__VA_ARGS__)
#define WARNc(...) Core::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ERRORc(...) Core::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define SUCCESS_msg "GREAT SUCESS"
#define WARNING_msg "Oh Wawaweewa..."
#define FAILURE_msg "PAIN IN MY ASSHOLES"

#define TIMER_START spdlog::stopwatch sw
#define TIMER_ELAPSEDc(...) Core::Log::GetCoreLogger()->debug(__VA_ARGS__, sw)

