#include "Log.h"


namespace A_LIFE
{
	void A_LIFE_Log::Init()
	{
		//CORE_LOGGER_SINK = spdlog::stdout_color_mt("A-LIFE");
		CORE_LOGGER_SINK = std::make_shared<spdlog::sinks::stdout_sink_st>();
		

		spdlog::logger CORE_LOGGER("A-LIFE", CORE_LOGGER_SINK);
		
		//spdlog::logger logger("Test", )
	}

}
