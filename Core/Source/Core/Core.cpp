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




	
/*
	// Thank you https://stackoverflow.com/a/850812
	void Print_CPU_Details()
	{
		int CPUInfo[4] = { -1 };
		unsigned   nExIds, i = 0;
		char CPUBrandString[0x40];

		// Get the information associated with each extended ID.
		__cpuid(CPUInfo, 0x80000000);
		nExIds = CPUInfo[0];

		for (i = 0x80000000; i <= nExIds; ++i)
		{
			__cpuid(CPUInfo, i);
			// Interpret CPU brand string
			if (i == 0x80000002)
				memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
			else if (i == 0x80000003)
				memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
			else if (i == 0x80000004)
				memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
		}

		INFOc("CPU Deatils are : {}", CPUBrandString);

		MEMORYSTATUSEX status;
		status.dwLength = sizeof(status);
		GlobalMemoryStatusEx(&status);
		INFOc("Total RAM available : ~{}GB", status.ullTotalPhys / 1024000000 );
		return;
	}
};
		*/

ALIFE_CoreObject::ALIFE_CoreObject()
{
	Name = "Unamed Object";

	Init_Log(Name);
}


ALIFE_CoreObject::ALIFE_CoreObject(const char* object_name)
{
	// idk how to check null string
	bool valid_name = (object_name == "") || (object_name == NULL) || (object_name == nullptr);
	Name = valid_name ? object_name : "Unnamed";
	
	Init_Log(object_name);
	if (valid_name)
		Warn("No name was given for this A-LIFE Object... changing it to %s", Name);
	
	else
		Verbose("Creating %s Object now", Name);
}

void ALIFE_CoreObject::Log(ELogLevel verbosity_level, const char* fmt, va_list args)
{
	
}

void ALIFE_CoreObject::Init_Log()
{
	Init_Log(Name);
}

void ALIFE_CoreObject::Init_Log(const char* new_logger_name)
{
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

void ALIFE_CoreObject::Error(const char* fmt, ...)
{
	va_list args;
	__crt_va_start(args, fmt);
	Log(ELogLevel::Error, fmt, args);
	__crt_va_end(args);
}

void ALIFE_CoreObject::OhShit(const char* fmt, ...)
{
	va_list args;
	__crt_va_start(args, fmt);
	Log(ELogLevel::CRITICAL, fmt, args);
	__crt_va_end(args);
}
