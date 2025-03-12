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



ALIFE_CoreObject::ALIFE_CoreObject()
{
	Name = "Unamed Object";
	BackLoggedLogs.reserve(128);
	//ReadyToLog = Init_Log();

}

bool ALIFE_CoreObject::RetrieveLogBacklog()
{
	ClearingBackLog = true;
	try
	{

		for (std::string msg : BackLoggedLogs) 
		{
			Verbose(msg.c_str());
		}
		BackLoggedLogs.clear();
		ClearingBackLog = false;
		return true;
	}
	catch (const std::exception&)
	{
		return false;
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

