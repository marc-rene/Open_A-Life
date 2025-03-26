#pragma once

#include "Core/Core.h"
#include "Modules/Director/Director.h"

namespace A_LIFE
{
	struct ALIFE_SCENARIO {
		Director director;
		ALIFE_CoreObject packet_ninja;
		static A_LIFE_Log Logger;
		const char* DEBUG_TestName = "Hello :)";

		ALIFE_SCENARIO()
		{
			Logger.Init();

			director = Director();
			director.Info("IT'S SHOOTIN' TIME!");
			//INFOc("AY HEY LETS GO");
		}

		void Init()
		{

			//Director.Info("%s is Ready!", Director.Name);

		}

		
	};
}