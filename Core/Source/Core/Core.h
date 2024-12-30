#pragma once

//#include "Log.h"
#include "Modules/Packet Ninja/Packet_Ninja.h"
#include "Modules/Director/Director.h"

#include "Core/Type_Definitions.hpp"



class ALIFE_CoreObject {

public:
	const char* Name;
	bool ReadyToLog = false;

	/**
	 * @brief Every Object needs to be created with a process name ("Packet Ninja", "Director", etc...)
	 * @param object_name: what's the name?
	 */
	ALIFE_CoreObject(const char* object_name);
	ALIFE_CoreObject();

	/**
	 * @brief The logging that every Open A-Life object should contain
	 * @param verbosity_level How important is this log??
	 */

	virtual void Log(ELogLevel verbosity_level, const char* fmt, va_list args);


	/**
	 * @brief Just in case you need to initialise a logger, 
	maybe with a new name?
	 * @param new_logger_name what name will the logger use?, leave BLANK to leave unchanged
	 */
	virtual void Init_Log(const char* new_logger_name);
	virtual void Init_Log();

	virtual void Verbose(const char* fmt, ...); // Verbose log... Same as Log(ELogLevel::Verbose)
	virtual void Info(const char* fmt, ...);	// Slightly more important log, same as Log(ELogLevel::Info)
	virtual void Warn(const char* fmt, ...);	// "Oh my!" log, same as Log(ELogLevel::Warning)
	virtual void Error(const char* fmt, ...);	// "OH BALLS" Log, same as Log(ELogLevel::Error)
	//virtual void OhShit(const char* fmt, ...);	// Something bad has happend, May this never be called
	
};

struct ALIFE_PAIRING {
	ALIFE_CoreObject Director;
	ALIFE_CoreObject Packet_Ninja;
};