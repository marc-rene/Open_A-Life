#pragma once

#include "Core/Core.h"
#include "Modules/Director/Director.h"
#include "Modules/Packet Ninja/Packet_Ninja.h"

namespace A_LIFE
{
    // FOR THE LOVE OF GOD THERE SHALL BE ONE SCENARIO UNTIL I FIGURE OUT HOW TF WE GONNA DO MULTIPLE OF THESE HEATHENS
    struct ALIFE_SCENARIO
    {
        inline static Director director;
        inline static Packet_Ninja packetNinja;
        inline static std::string scenarioName;
        inline static std::vector<const std::string*> allLevels;
        static A_LIFE_Log logger;

        ALIFE_SCENARIO();

        void Init();
        static void GetAllLevelsFromRuntimeRegistry();

        ~ALIFE_SCENARIO();

    private:
        // We are running ONE version of this Scenario
        // TODO: Get this version from a GIT build or something, not hardcoded
        static inline auto VERSION = LOCAL_ALIFE_VERSION;
    };
}
