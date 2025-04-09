#include "Core.h"
#include <stdint.h>
//#include "Log.h"
//#include "File_Wizard.h"
//#include "Director.h"
//#include "Packet_Ninja.h"

//#include <future>
//#include <chrono>
//#include <iostream>


//using namespace std::chrono_literals;

namespace A_LIFE 
{
	ALIFE_CoreObject::ALIFE_CoreObject()
	{
		Name = "Borat!";
	}

	ALIFE_CoreObject::ALIFE_CoreObject(const char* ObjectName)
	{
		Name = ObjectName;
	}

	void ALIFE_CoreObject::Init()
	{
		A_LIFE_Log::Init(Name);
	}


	void ALIFE_CoreObject::Log(ELogLevel verbosity, const char* fmt, va_list args)
	{
		std::string formatted = fmt::vformat(fmt, fmt::make_format_args(args));
		
		// FIX THIS BROKEN SHIT!
		switch (verbosity)
		{
		case ELogLevel::Verbose:
			ObjectLogger.GetLogger(Name)->trace(formatted);
			break;
		case ELogLevel::Info:
			ObjectLogger.GetLogger(Name)->info(formatted);
			break;
		case ELogLevel::Warning:
			ObjectLogger.GetLogger(Name)->warn(formatted);
			break;
		case ELogLevel::Error:
			ObjectLogger.GetLogger(Name)->critical(formatted);
			break;
		default:
			break;
		}
	}

	void ALIFE_CoreObject::Verbose(const char* fmt, ...)
	{
		va_list args;
		__crt_va_start(args, fmt);
		Log(ELogLevel::Verbose, fmt, args);
		__crt_va_end(args);
	}

	void ALIFE_CoreObject::Info(const char* fmt, ...)
	{
		va_list args;
		__crt_va_start(args, fmt);
		Log(ELogLevel::Info, fmt, args);
		__crt_va_end(args);
	}

	void ALIFE_CoreObject::Warn(const char* fmt, ...)
	{
		va_list args;
		__crt_va_start(args, fmt);
		Log(ELogLevel::Warning, fmt, args);
		__crt_va_end(args);
	}

	// Oh crap...
	void ALIFE_CoreObject::Error(const char* fmt, ...)
	{
		va_list args;
		__crt_va_start(args, fmt);
		Log(ELogLevel::Error, fmt, args);
		__crt_va_end(args);
	}
}
