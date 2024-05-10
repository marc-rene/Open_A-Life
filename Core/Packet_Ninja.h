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



namespace Core
{
	class Packet_Ninja
	{
	public:
		static mint Init();
		
		static mint Wait_For_Connection();
		
		
		static mint Test_Send_Packets();

		//#if is_windows_os
		
		//#else
				//TODO : Get Linux code
		//#endif
	};
}
