#pragma once

//#include "Log.h"
#include "Packet_Ninja.h"
#include "Director.h"
//#include "File_Wizard.h"
#include "Type_Definitions.hpp"



namespace Core {

	class OPEN_ALIFE_CORE {
	public:
		const char* Name;
		Core::Packet_Ninja TCPer;
		Core::Director Tarantino;

		
	};

	/*	Create our ports for listening to and sending commands.
		We also need to load our scenario, make sure everything is ready to go!*/
	void Initialise();

	void Print_CPU_Details();
}