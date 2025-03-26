#pragma once

#include "Core/Core.h"
#include "Modules/Director/Director.h"

namespace A_LIFE
{
	struct ALIFE_SCENARIO {
		Director director;
		ALIFE_CoreObject packet_ninja;
		A_LIFE_Log Logger;
		const char* DEBUG_TestName = "Hello :)";

		ALIFE_SCENARIO()
		{
			Logger.Init();

			
			director = Director();
			SetReadyToLog(true);
			//director.Info("IT'S SHOOTIN' TIME!");
			INFOc("AY HEY LETS GO");
		}

		void Init()
		{

			//Director.Info("%s is Ready!", Director.Name);

		}

		void SetReadyToLog(bool isReady)
		{
			director.ReadyToLog = isReady;
			packet_ninja.ReadyToLog = isReady;

			if (isReady == true)
			{
				if (director.BackLoggedLogs.size() > 0)
					director.RetrieveLogBacklog();

				if (packet_ninja.BackLoggedLogs.size() > 0)
					packet_ninja.RetrieveLogBacklog();
			}
		}
	};
}