#include "Log.h"

#include <iostream>


namespace A_LIFE
{
    std::shared_ptr<spdlog::logger> A_LIFE_Log::Init_Log()
    {
        return A_LIFE_Log::Init_Log("A-LIFE");
    }

    std::shared_ptr<spdlog::logger> A_LIFE_Log::Init_Err_Log()
    {
        try
        {
            std::shared_ptr<spdlog::logger> errorLogger = spdlog::stdout_color_mt("A-ERROR");
            spdlog::set_error_handler([](const std::string& msg)
            {
                spdlog::get("A-ERROR")->error("*** {} ***: {}", FAILURE_msg, msg);
            });

            return errorLogger;
        }
        catch (const spdlog::spdlog_ex&)
        {
            return spdlog::get("A-ERROR");
        }
    }

    std::shared_ptr<spdlog::logger> A_LIFE_Log::Init_Log(const char* LoggerName)
    {
        if (Init_Err_Log() == nullptr)
        {
            //todo: Add error log init failure catch here
        }

        try
        {
            // Thanks https://www.w3schools.com/cpp/trycpp.asp?filename=demo_date_strftime
            time_t timestamp = time(NULL);
            struct tm datetime = *localtime(&timestamp);
            char formatted_date[50];
            strftime(formatted_date, 50, "%a  %e %b %H-%M", &datetime); 

            auto frontEndConsoleSink    = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            std::string filename        = std::format("{}/logs/{} ALIFE_{}.log", std::filesystem::current_path().string(),  formatted_date, LOCAL_ALIFE_VERSION.to_string());
            auto fileSink               = std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename, true );
            std::vector<spdlog::sink_ptr> sinks{frontEndConsoleSink, fileSink};

            // ---------------------
            // ASYNC IMPLEMENTATION |
            // ---------------------
            //if (total_inits == 0)
            //    spdlog::init_thread_pool(8192, 1);
            //auto logger =       std::make_shared<spdlog::async_logger>(LoggerName, sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::overrun_oldest);

            auto logger =     std::make_shared<spdlog::logger>(LoggerName, sinks.begin(), sinks.end());
            logger->set_level(spdlog::level::trace); // or info/warn
            spdlog::register_logger(logger);
            total_inits++;

            return logger;
        }
        catch (const spdlog::spdlog_ex& ex) // Logger probably already exists
        {
            std::cout << "Hey, Just so you know, we got SPDLOG tomfoolery here because " << ex.what() << std::endl;
            return spdlog::get(LoggerName);
        }
    }

    std::shared_ptr<spdlog::logger> A_LIFE_Log::GetLogger()
    {
        return A_LIFE_Log::GetLogger("A-LIFE");
    }

    std::shared_ptr<spdlog::logger> A_LIFE_Log::GetLogger(const std::string LoggerName)
    {
        return A_LIFE_Log::GetLogger(LoggerName.c_str());    
    }
    
    std::shared_ptr<spdlog::logger> A_LIFE_Log::GetLogger(const char* LoggerName)
    {
        // Use Init instead because if the logger doesn't exist we'll make one..very sketch
        if (spdlog::get(LoggerName) == nullptr)
        {
            WARNc("HEY! {} DOESN'T EXIST YET... Making him now", LoggerName);
            A_LIFE_Log::Init_Log(LoggerName);
        }

        return spdlog::get(LoggerName);
    }
}
