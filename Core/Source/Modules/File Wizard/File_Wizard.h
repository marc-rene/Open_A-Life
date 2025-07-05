#pragma once 



#include "Core/Type_Definitions.h"
#include <filesystem>




namespace A_LIFE
{
    struct System_Information
    {
        std::string OS_name;
        std::string CPU_name;
        std::string CPU_arch;
        uInt CPU_core_count;
        uFatty CPU_thread_count;
        uFatty CPU_cache_bytes_per_thread;

        uFatty RAM_total_amount;
        uFatty RAM_available_amount;

        uFatty STORAGE_total;
        uFatty STORAGE_free;


        static std::string Get_OS_Name();
        static std::string Get_CPU_Name();
        static std::string Get_CPU_arch();
        static uInt Get_CPU_core_count();
        static uFatty Get_CPU_thread_count();
        static uFatty Get_CPU_cache_bytes_per_thread();
        static uFatty Get_CPU_cache_bytes_total() { return Get_CPU_thread_count() * Get_CPU_cache_bytes_per_thread(); }
        static uFatty Get_RAM_total_amount();
        static uFatty Get_RAM_available_amount();
        static uFatty Get_STORAGE_total();
        static uFatty Get_STORAGE_free();

        System_Information() :
            OS_name(Get_OS_Name()),
            CPU_name(Get_CPU_Name()),
            CPU_arch(Get_CPU_arch()),
            CPU_core_count(Get_CPU_core_count()),
            CPU_thread_count(Get_CPU_thread_count()),
            CPU_cache_bytes_per_thread(Get_CPU_cache_bytes_per_thread()),
            RAM_total_amount(Get_RAM_total_amount()),
            RAM_available_amount(Get_RAM_available_amount()),
            STORAGE_total(Get_STORAGE_total()),
            STORAGE_free(Get_STORAGE_free())
        {
        }
    };


    struct File_Wizard
    {
        static std::string List_Environment_Vars();

        /// 
        /// @param INI_File What INI file do we want to check exist? 
        /// @param make_new_if_not_exist if the ini doesn't exist, should we make a new one?
        /// @return True if we found the file and didn't need to make one, False if not or if we had to make a new ini
        static bool Does_INI_Exist(std::filesystem::path INI_File, bool make_new_if_not_exist);

        /// 
        /// @param INI_File What ini file do we want to edit?
        /// @param Section What section of the ini are we getting?
        /// @return True if value was successfully set, false if not
        static bool Set_INI_Setting(std::filesystem::path INI_File, std::string Section, std::string Key,
                                    std::string Value);

        static const std::string Get_INI_Setting(std::filesystem::path INI_File, std::string Section,
                                                 std::string Key);

        static std::filesystem::path SetSavePath(const char* Filter, const char* File_Extention,
                                                 const char* Default_Filename, const char* Dialog_Title);
        static std::filesystem::path OpenFilePath(const char* Filter, const char* File_Extention, const char* Dialog_Title);

        static std::vector<std::string> Get_CSV_Column_Data(std::filesystem::path CSV_File,
                                                            std::string Column_Name,
                                                            uInt allocation_size);


        static bool Prompt_Confirm(std::string Title, std::string Description);
        static bool Prompt_Retry(std::string Title, std::string Description);
        static mint test_csv_io();
        static mint test_ini_io();

        // Defining here because compiler is complaining
        //template <typename floatType, typename intType>
        //static bool OBJ_to_Mesh(std::filesystem::path obj_file_path, std::pair<std::vector<floatType>, std::vector<intType>>* mesh_buffer);
        //static bool OBJ_to_Mesh(std::filesystem::path obj_file_path, std::pair<std::vector<float>, std::vector<int>>* mesh_buffer);
            /*
        {
            tinyobj::attrib_t attrib;
            std::vector<tinyobj::shape_t> shapes;
            std::vector<tinyobj::material_t> materials;
            std::string warning_msg, error_msg; 

            bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warning_msg, &error_msg, obj_file_path.string().c_str());

            if (!ret)
            {
                //WARN("File Wizard", "We couldn't load {} because {} or {}", obj_file_path.string(), warning_msg, error_msg);
                return false;
            }

            std::vector<floatType> vertices;
            std::vector<intType> indices;

            for (const auto& shape : shapes)
            {
                for (const auto& index : shape.mesh.indices)
                {
                    floatType vx = attrib.vertices[3 * index.vertex_index + 0];
                    floatType vy = attrib.vertices[3 * index.vertex_index + 1];
                    floatType vz = attrib.vertices[3 * index.vertex_index + 2];

                    vertices.push_back(vx);
                    vertices.push_back(vy);
                    vertices.push_back(vz);
                }

                for (size_t i = 0; i < shape.mesh.indices.size(); i += 3)
                {
                    indices.push_back(static_cast<intType>(i + 0));
                    indices.push_back(static_cast<intType>(i + 1));
                    indices.push_back(static_cast<intType>(i + 2));
                }
            }
            mesh_buffer->first = vertices;
            mesh_buffer->second = indices;
            return true;
        }
            */
    };
}
