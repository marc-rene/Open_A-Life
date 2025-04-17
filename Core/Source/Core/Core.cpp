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

	ALIFE_CoreObject::ALIFE_CoreObject(const std::string ObjectName)
	{
		Name = ObjectName;
	}

	void ALIFE_CoreObject::Init()
	{
		A_LIFE_Log::Init_Log(Name.c_str());
	}


	void ALIFE_CoreObject::Log(ELogLevel verbosity, std::string msg)
	{
		switch (verbosity)
		{
		case ELogLevel::Verbose:
			ObjectLogger.GetLogger(Name)->trace(msg);
			break;
		case ELogLevel::Info:
			ObjectLogger.GetLogger(Name)->info(msg);
			break;
		case ELogLevel::Warning:
			ObjectLogger.GetLogger(Name)->warn(msg);
			break;
		case ELogLevel::Error:
			ObjectLogger.GetLogger(Name)->critical(msg);
			break;
		default:
			break;
		}
	}


	//todo: fix this horrible chatgpt insanity. it doesn't know how spdlog works with fmt and my 4 hour sleep brain
	// is not equipped to deal with this nonsense. so for now, all logs made using object directly need to use c-style
	// delimeters like %d and %s instead of fmt {}

	//Update: I've given up... all directly called logs will use fmt::format() or something
	void ALIFE_CoreObject::Verbose(std::string msg)
	{
		Log(ELogLevel::Verbose, msg);
	}

	void ALIFE_CoreObject::Info(std::string msg)
	{
		Log(ELogLevel::Info, msg);
	}

	void ALIFE_CoreObject::Warn(std::string msg)
	{
		Log(ELogLevel::Warning, msg);
	}

	// Oh crap...
	void ALIFE_CoreObject::Error(std::string msg)
	{
		Log(ELogLevel::Error, msg);
	}
}
