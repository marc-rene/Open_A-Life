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
		static std::shared_ptr<spdlog::logger> Init();
		static std::shared_ptr<spdlog::logger> Init(const char* LoggerName);

		static std::shared_ptr<spdlog::logger> GetLogger();
		static std::shared_ptr<spdlog::logger> GetLogger(const char* LoggerName);
	};
}





#define INFOc(...)		spdlog::get("A-LIFE")->info(__VA_ARGS__)
#define SUCCESSc(...)	spdlog::get("A-LIFE")->info(__VA_ARGS__)
#define WARNc(...)		spdlog::get("A-LIFE")->warn(__VA_ARGS__)
#define ERRORc(...)		spdlog::get("A-LIFE")->critical(__VA_ARGS__)

#define SUCCESS_msg "GREAT SUCESS"
#define WARNING_msg "Oh Wawaweewa..."
#define FAILURE_msg "PAIN IN MY ASSHOLES"

#define TIMER_START spdlog::stopwatch sw
#define TIMER_ELAPSEDc(...) Core::Log::GetCoreLogger()->debug(__VA_ARGS__, sw)

