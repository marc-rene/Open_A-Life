#pragma once
#include "Core/Type_Definitions.h"

#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/stopwatch.h"
#include "spdlog/sinks/callback_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/async.h"


/*
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/stopwatch.h"
*/

namespace A_LIFE
{
    class A_LIFE_Log
    {
    public:
        static std::shared_ptr<spdlog::logger> Init_Log();
        static std::shared_ptr<spdlog::logger> Init_Err_Log();
        static std::shared_ptr<spdlog::logger> Init_Log(const char* LoggerName);

        static std::shared_ptr<spdlog::logger> GetLogger();
        static std::shared_ptr<spdlog::logger> GetLogger(std::string LoggerName);
        static std::shared_ptr<spdlog::logger> GetLogger(const char* LoggerName);

    private:
        static inline uShort total_inits = 0;
    };
}


#define INFOc(...)					{try{A_LIFE::A_LIFE_Log::GetLogger()->trace(__VA_ARGS__);}catch(const std::exception& e){std::cout<<std::format("\n! Trace log error: {}!\n",e.what())<<std::format(__VA_ARGS__);}}
#define INFO(logger_name, ...)		{try{A_LIFE::A_LIFE_Log::GetLogger(logger_name)->trace(__VA_ARGS__);}catch(const std::exception& e){std::cout<<std::format("\n!Trace log error: {}!\n",e.what())<<std::format(__VA_ARGS__);}}

#define SUCCESSc(...)				{try{A_LIFE::A_LIFE_Log::GetLogger()->info(__VA_ARGS__);}catch(const std::exception& e){std::cout<<std::format("\n!!!INFO LOG ERROR: {}!!!\n",e.what())<<std::format(__VA_ARGS__);}}
#define SUCCESS(logger_name, ...)	{try{A_LIFE::A_LIFE_Log::GetLogger(logger_name)->info(__VA_ARGS__);}catch(const std::exception& e){std::cout<<std::format("\n!!!INFO LOG ERROR: {}!!!\n",e.what())<<std::format(__VA_ARGS__);}}
#define WARNc(...)					{try{A_LIFE::A_LIFE_Log::GetLogger()->trace(__VA_ARGS__);}catch(const std::exception& e){std::cout<<std::format("\n!!!WARN LOG ERROR: {}!!!\n",e.what())<<std::format(__VA_ARGS__);}}
#define WARN(logger_name, ...)		{try{A_LIFE::A_LIFE_Log::GetLogger(logger_name)->trace(__VA_ARGS__);}catch(const std::exception& e){std::cout<<std::format("\n!!!WARN LOG ERROR: {}!!!\n",e.what())<<std::format(__VA_ARGS__);}}

#define ERRORc(...)					{try{A_LIFE::A_LIFE_Log::GetLogger("A-HUGE-ERROR")->critical(__VA_ARGS__);}catch(const std::exception& e){std::cout<<std::format("\n!!!FUCK FUCK ERROR: {}!!!\n",e.what())<<std::format(__VA_ARGS__);}}
//#define ERROR(logger_name, ...)		A_LIFE::A_LIFE_Log::GetLogger("A-HUGE-ERROR")->critical(__VA_ARGS__); A_LIFE::A_LIFE_Log::GetLogger(logger_name)->critical(__VA_ARGS__)

#define SUCCESS_msg		"GREAT SUCESS"
#define WARNING_msg		"Oh Wawaweewa..."
#define FAILURE_msg		"PAIN IN MY ASSHOLES"
#define FAREWELL_msg	"Good Hunting S.t.a.l.k.e.r"

#define TIMER_START spdlog::stopwatch sw
#define TIMER_ELAPSEDc(...)					A_LIFE::A_LIFE_Log::GetLogger("A-LIFE")->trace(__VA_ARGS__, sw)		// Usage: TIMER_ELAPSEDc("Taken {:.3) seconds so far!)

#define TIMER_ELAPSED(logger_name, ...)		A_LIFE::A_LIFE_Log::GetLogger(logger_name)->trace(__VA_ARGS__, sw)	// Usage: TIMER_ELAPSEDc("Taken {:.3) seconds so far!)
