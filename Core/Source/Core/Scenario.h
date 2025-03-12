#pragma once

#include "Core/Core.h"
#include "Modules/Director/Director.h"


struct ALIFE_SCENARIO {
	Director Director;
	ALIFE_CoreObject Packet_Ninja;

	void Init()
	{
		Director = Director::Director();
		SetReadyToLog(true);
		Director.Info("%s is Ready!", Director.Name);

	}

	void SetReadyToLog(bool isReady)
	{
		Director.ReadyToLog = isReady;
		Packet_Ninja.ReadyToLog = isReady;

		if (isReady == true)
		{
			if (Director.BackLoggedLogs.size() > 0)
				Director.RetrieveLogBacklog();

			if (Packet_Ninja.BackLoggedLogs.size() > 0)
				Packet_Ninja.RetrieveLogBacklog();
		}
	}
};
