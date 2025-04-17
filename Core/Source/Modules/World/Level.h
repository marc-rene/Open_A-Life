#pragma once
#include "Core/Core.h"

namespace A_LIFE
{
    class Level : public ALIFE_CoreObject
    {
        #define LevelName Name
        inline static std::vector<std::string> AllRegisteredLevels;
        std::string DisplayName;
        
    public:
        Level(const std::string levelName);
    };
}
