#pragma once
#include "Type_Definitions.hpp"



enum class EMsg_Priority : uMint
{
	Verbose =	BIT(0),
	Info	=	BIT(1),
	Warning	=	BIT(2),
	Error	=	BIT(3)
};

namespace Core
{
	class BaseLog
	{
		EMsg_Priority Priority_Filter;

		// Do we need to initialise our logger? Well here's a method for that, just incase
		virtual BaseLog Init_Logger();

		// Log a message with a certain priority, all messages are verbose by default
		virtual void Log(EMsg_Priority priority, const char* message);

		//
		virtual void Change_Priority(EMsg_Priority new_priority_filter);
	};
}
