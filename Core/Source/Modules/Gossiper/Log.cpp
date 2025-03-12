#include "Log.h"

#include <iostream>
#include <exception>

namespace Core
{

	//static inline std::shared_ptr<spdlog::logger> CoreLogger;
	//static inline std::shared_ptr<spdlog::logger> EngineLogger;



	mint Log::Init()
	{/*
		spdlog::set_pattern("%^[%T] %n: %v%$");
		try {

			
			// Create a file rotating logger with 5 MB size max and 3 rotated files
			auto max_size = 1048576 * 5;
			auto max_files = 3;
			CoreLogger = spdlog::rotating_logger_mt("Core", "Logs/Log_History.log", max_size, max_files);
			//

			CoreLogger = spdlog::stdout_color_mt("Core");
			CoreLogger->set_level(spdlog::level::trace);
			
			SUCCESSc("Core Logger has been initialised, {}", SUCCESS_msg);
		}
		catch (std::exception ex)
		{
			std::cout << "### " << FAILURE_msg << " : CORE LOGGER COULD NOT BE INITIALISED ###" << std::endl;
			std::cout << ex.what() << std::endl;
			return 1;
		}

		try
		{
			EngineLogger = spdlog::stdout_color_mt("Engine");
			EngineLogger->set_level(spdlog::level::trace);
			SUCCESSe("Engine Logger has been initialised, {}", SUCCESS_msg);
		}
		catch (std::exception ex)
		{
			std::cout << "### " << FAILURE_msg << " : ENGINE LOGGER COULD NOT BE INITIALISED ###" << std::endl;
			std::cout << ex.what() << std::endl;
			return 2;
		}

		//INFOc("Info Log Style");
		//SUCCESSc("Success Log Style"); 
		//WARNc("Warning Log Style");
		//ERRORc("CORE Error Log Style");
		//ERRORe("Engine Error Log Style");

		*/
		return 0;
	}

}
