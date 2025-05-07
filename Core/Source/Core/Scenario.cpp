#include "Scenario.h"

namespace A_LIFE
{
    ALIFE_SCENARIO::ALIFE_SCENARIO()
    {
        logger.Init_Log();
        scenarioName = "Salut!";
        allLevels = {};
        INFOc("Running on these specs: {}", File_Wizard::List_Environment_Vars());
    }

    void ALIFE_SCENARIO::GetAllLevelsFromRuntimeRegistry()
    {
        for (const auto& level : ALIFE_CoreObject::ObjectRegistry)
        {
            if (level.second->ObjectType == EObjectType::LEVEL)
                allLevels.push_back(&level.first);
        }
    }
    
    ALIFE_SCENARIO::~ALIFE_SCENARIO()
    {
        SUCCESSc("\nThe {} Scenario has finished..."
                 "\nThe drapes have been draped..."
                 "\nThe prayer to the gods for a successful run/exit,"
                 "\n...have hopefully been answered"
                 "\n\nIf not, drop me a Github issue and i'll reply", scenarioName);
    }

    void ALIFE_SCENARIO::Init()
    {
        INFOc("The {} show is about to begin!", scenarioName);
        director.Init();
        packetNinja.Init();
        GetAllLevelsFromRuntimeRegistry();
    }
}
