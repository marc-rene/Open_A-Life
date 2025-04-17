#pragma once

#include "Modules/Gossiper/Log.h"

#include <iostream>
#include <memory>
#include "Core/Type_Definitions.hpp"


namespace A_LIFE
{
	class ALIFE_CoreObject {

	public:
		const char* Name;
		std::vector<std::unique_ptr<ALIFE_CoreObject>> ObjectRegistry;
		std::vector<std::string> BackLoggedLogs;
		static A_LIFE::A_LIFE_Log ObjectLogger;

		/**
		 * @brief Every Object needs to be created with a process name ("Packet Ninja", "Director", etc...)
		 * @param object_name: what's the name?
		 */
		
		ALIFE_CoreObject();
		ALIFE_CoreObject(const char* ObjectName);
		virtual void Init();

		/**
		 * @brief The logging that every Open A-Life object should contain
		 * @param verbosity_level How important is this log??
		 */

		virtual void Log(ELogLevel verbosity_level, const char* fmt, va_list args);


	


		virtual void Verbose(const char* fmt, ...); // Verbose log... Same as Log(ELogLevel::Verbose)
		virtual void Info(const char* fmt, ...);	// Slightly more important log, same as Log(ELogLevel::Info)
		virtual void Warn(const char* fmt, ...);	// "Oh my!" log, same as Log(ELogLevel::Warning)
		virtual void Error(const char* fmt, ...);	// "OH BALLS" Log, same as Log(ELogLevel::Error)

	};
}
