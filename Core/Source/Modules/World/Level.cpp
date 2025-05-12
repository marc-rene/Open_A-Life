#include "Level.h"

namespace A_LIFE
{
    Level::Level(const std::string levelName) : ALIFE_CoreObject(levelName, EObjectType::LEVEL)
    {
        LevelMeshData = {};
    };

    void Level::SetStaticMeshData(std::filesystem::path object_file_path)
    {
        std::pair<std::vector<float>, std::vector<int>> mesh_buffer;
        /*if (File_Wizard::OBJ_to_Mesh(object_file_path, &mesh_buffer))
        {
            LevelMeshData.vertices = mesh_buffer.first;
            LevelMeshData.indices = mesh_buffer.second;
        }
        else
        {
            WARNc("{} failed to load object file: {}", ObjectName, object_file_path.string());
        }*/
        return;
    }
}
