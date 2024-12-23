#pragma once

//#include "Log.h"
#include "Type_Definitions.hpp"
#include "Modules/Packet Ninja/Packet_Ninja.h"
#include "Modules/Director/Director.h"
//#include "File_Wizard.h"


namespace Core {
	class OPEN_ALIFE {

	public:
		Core::Director Tarantino;
		Core::Packet_Ninja PNinja;

		/*	Create our ports for listening to and sending commands.
			We also need to load our scenario, make sure everything is ready to go!*/
		void Initialise();

		void Print_CPU_Details();
	};
}