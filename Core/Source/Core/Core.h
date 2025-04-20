#pragma once

#include "Modules/Gossiper/Log.h"
#include "Modules/File Wizard/File_Wizard.h"

#include <iostream>
#include <memory>
#include "Core/Type_Definitions.hpp"


namespace A_LIFE
{
    class ALIFE_CoreObject
    {
    public:
        std::string Name;
        std::vector<std::unique_ptr<ALIFE_CoreObject>> ObjectRegistry;
        std::vector<std::string> BackLoggedLogs;
        A_LIFE::A_LIFE_Log ObjectLogger;

        /**
         * @brief Every Object needs to be created with a process name ("Packet Ninja", "Director", etc...)
         * @param object_name: what's the name?
         */
        ALIFE_CoreObject(const std::string ObjectName);
        ALIFE_CoreObject();
        virtual void Init();

        /**
         * @brief The logging that every Open A-Life object should contain
         * @param verbosity_level How important is this log??
         */
        virtual void Log(ELogLevel verbosity_level, std::string msg);

        virtual void Verbose(std::string msg); // Verbose log... Same as Log(ELogLevel::Verbose)
        virtual void Info(std::string msg); // Slightly more important log, same as Log(ELogLevel::Info)
        virtual void Warn(std::string msg); // "Oh my!" log, same as Log(ELogLevel::Warning)
        virtual void Error(std::string msg); // "OH BALLS" Log, same as Log(ELogLevel::Error)
    };
}
