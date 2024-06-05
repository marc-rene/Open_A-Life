#pragma once
#include "Core.h" 
#include "Type_Definitions.hpp"
#include <stdlib.h>


//#define is_windows_os 1	//defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__) 
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

//#if is_windows_os
#include <ws2tcpip.h>
#include <winsock2.h>
#pragma comment (lib, "Ws2_32.lib")

//#else // probably linux?

//#endif

enum class State {

};

namespace Core
{
	class Packet_Ninja
	{
	public:
		static mint Init();
		
		static mint Create_Socket(mint preffered_port);

		static mint Wait_For_Connection();
		
		static mint On_Connection_Established();

		static mint Send_Generic_String(const char* data);
		static mint Send_Value(const char* key, const char* value);
		static mint Send_Controlled_Message(StateFlag current_state );

		static mint On_Message_Recieved();


		//#if is_windows_os
		
		//#else
				//TODO : Get Linux code
		//#endif
	};
}
