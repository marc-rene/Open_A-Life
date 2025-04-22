#include "Scenario.h"

namespace A_LIFE
{
    ALIFE_SCENARIO::ALIFE_SCENARIO()
    {
        logger.Init_Log();
        scenarioName = "Salut!";
        INFOc("Running on these specs: {}", File_Wizard::List_Environment_Vars());
        INFOc("Starting ALIFE scenario pre-init steps with version {}", VERSION.to_string());

        director = Director();
        packetNinja = Packet_Ninja();

        INFOc("{} has finished pre-init steps", scenarioName);
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
    }
}