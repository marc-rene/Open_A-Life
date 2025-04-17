#include "Level.h"

namespace A_LIFE
{
    Level::Level(const std::string levelName)
    {
        ALIFE_CoreObject::ALIFE_CoreObject(levelName.c_str());

        
        for (std::string level : AllRegisteredLevels)
        {
            if (level == levelName)
            {
                WARNc("HEY! {} is already a level, you can't have duplicate levels!", LevelName);
                Level::~Level();
            }
            INFO(levelName.c_str(), "{} has been added to the Level register!", LevelName);
        }
    };
}
