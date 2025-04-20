#pragma once

#include "Core/Type_Definitions.hpp"
#include <filesystem>

namespace A_LIFE
{
    struct File_Wizard
    {
        /// 
        /// @return Returns map in the form <Variable Name, Value>
        static std::unordered_map<std::string, std::string> Get_Environment_Vars();
        static std::string List_Environment_Vars(const char delimiter = '\n');

        /// 
        /// @param INI_File What INI file do we want to check exist? 
        /// @param make_new_if_not_exist if the ini doesn't exist, should we make a new one?
        /// @return True if we found the file and didnt need to make one, False if not or if we had to make a new ini
        static bool Does_INI_Exist(std::filesystem::path INI_File, bool make_new_if_not_exist);

        /// 
        /// @param INI_File What ini file do we want to edit?
        /// @param Section What section of the ini are we getting?
        /// @return True if value was successfully set, false if not
        static bool Set_INI_Setting(std::filesystem::path INI_File, const std::string Section, const std::string Key,
                                    const std::string Value);
        static const std::string Get_INI_Setting(std::filesystem::path INI_File, const std::string Section,
                                                 const std::string Key);

        static std::filesystem::path SetSavePath();
        
        static std::vector<std::string> Get_CSV_Column_Data(std::filesystem::path CSV_File,
                                                            const std::string Column_Name,
                                                            const unsigned int allocation_size);

        static mint test_csv_io();
        static mint test_ini_io();
    };
}
