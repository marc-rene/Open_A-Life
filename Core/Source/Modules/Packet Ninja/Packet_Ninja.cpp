#include "Packet_Ninja.h"
#include <future>

namespace Core
{
	// Server Side
	mint Packet_Ninja::Start_Server(uShort port)
	{
		return 1;
	};

	mint Packet_Ninja::Accept_Connection()
	{
		return 1;
	};


	// Client Side
	mint Packet_Ninja::Connect_To_Port(uShort port)
	{
		return 1;
	};

	// Shared
	mint Packet_Ninja::Send_Value(const char* key, const char* value)
	{
		return 1;
	};


}