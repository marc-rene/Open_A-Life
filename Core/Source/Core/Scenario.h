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
        static A_LIFE_Log logger;
        inline static std::string scenarioName;

        ALIFE_SCENARIO();

        void Init();

        ~ALIFE_SCENARIO()
        {
            //INFOc("Destroying Scenario Codename \"{}\" \n\n{}", );
        }

    private:
        // We are running ONE version of this Scenario
        // TODO: Get this version from a GIT build or something, not hardcoded
        static inline ALIFE_Version VERSION = ALIFE_Version(1, 0, 0);
    };
}
