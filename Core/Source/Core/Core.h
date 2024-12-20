#pragma once

//#include "Log.h"
//#include "Packet_Ninja.h"
//#include "File_Wizard.h"
#include "Type_Definitions.hpp"



namespace Core {

	class OPEN_ALIFE_CORE {
	public:
		int UID;

		
	};

	/*	Create our ports for listening to and sending commands.
		We also need to load our scenario, make sure everything is ready to go!*/
	void Initialise();

	bool Create_Listening_Port();
	void Set_Listening_Port();

	bool Create_Broadcast_Port();
	void Set_Broadcasting_Port();

	void Print_CPU_Details();
}