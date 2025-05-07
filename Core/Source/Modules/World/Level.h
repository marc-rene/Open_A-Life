#pragma once
#include "Core/Core.h"

namespace A_LIFE
{
    struct MeshData
    {
        std::vector<float> vertices;
        std::vector<int> indices;
    };

    class Level : public ALIFE_CoreObject
    {
    public:
        MeshData LevelMeshData;

        void SetStaticMeshData(std::filesystem::path obj_file_path);
        void SetStaticMeshData(MeshData staticMeshData);
        
        Level(const std::string levelName);
    };
}
