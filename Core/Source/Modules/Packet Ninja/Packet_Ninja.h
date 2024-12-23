#pragma once
#include "Type_Definitions.hpp"


namespace Core
{
	class Packet_Ninja
	{
	
		uShort port_number;

	public:		
		// Server Side
		static mint Start_Server(uShort port);
		static mint Accept_Connection();
		
		// Client Side
		static mint Connect_To_Port(uShort port);

		// Shared
		static mint Send_Value(const char* key, const char* value);
		static uShort Get_Port();
	};
}
