#include "Scenario.h"

namespace A_LIFE
{
    ALIFE_SCENARIO::ALIFE_SCENARIO()
    {
        logger.Init_Log();
        scenarioName = "Salut!";
        INFOc("Running on these specs: {}\0", File_Wizard::List_Environment_Vars());
        INFOc("Starting ALIFE scenario pre-init steps with version {}", VERSION.to_string());

        director = Director();
        packetNinja = Packet_Ninja();

        INFOc("{} has finished pre-init steps", scenarioName);
        
    }

    void ALIFE_SCENARIO::Init()
    {
        INFOc("The {} show is about to begin!", scenarioName);
        director.Init();
        packetNinja.Init();
    }
}