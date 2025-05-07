#pragma once

#include "../Source/Modules/Gossiper/Log.h"
#include "../Source/Modules/File Wizard/File_Wizard.h"

#include <iostream>
#include <memory>
#include <map>
#include "Core/Type_Definitions.h"


namespace A_LIFE
{
    enum EObjectType : uMint // Using Unreal Engine terminology
    {
        OBJECT = 0, // something that is just PURE data
        LEVEL = 1,
        ACTOR = 2, // something that exists in the world
    };


    class ALIFE_CoreObject
    {
    public:
        const std::string ObjectName;
        const EObjectType ObjectType = OBJECT;
        inline static std::map<const std::string, ALIFE_CoreObject*> ObjectRegistry = {};
        std::vector<std::string> BackLoggedLogs;
        A_LIFE_Log ObjectLogger;

        /**
         * @brief Every Object needs to be created with a process name ("Packet Ninja", "Director", etc...)
         * @param object_name: what's the name?
         */
        ALIFE_CoreObject(std::string ObjectName, EObjectType ObjectType = OBJECT);
        ~ALIFE_CoreObject();

        ALIFE_CoreObject(); // This should NEVER be called

        static std::string ListObjectRegistry(const char* delimiter = "\n")
        {
            std::stringstream ss;
            ss.clear();

            for (const auto& [UID, objPtr] : ObjectRegistry)
            {
                ss << objPtr->ObjectName << delimiter;
            }

            return ss.str();
        }

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
