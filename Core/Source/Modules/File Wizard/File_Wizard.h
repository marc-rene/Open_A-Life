#pragma once

#include "Core/Type_Definitions.hpp"
#include <filesystem>

#

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
        static uInt     Get_CPU_core_count();
        static uFatty   Get_CPU_thread_count();
        static uFatty   Get_CPU_cache_bytes_per_thread();
        static uFatty   Get_CPU_cache_bytes_total()    { return Get_CPU_thread_count() * Get_CPU_cache_bytes_per_thread(); }
        static uFatty   Get_RAM_total_amount();
        static uFatty   Get_RAM_available_amount();
        static uFatty   Get_STORAGE_total();
        static uFatty   Get_STORAGE_free();

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
        {}
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
        static bool Set_INI_Setting(std::filesystem::path INI_File, const std::string Section, const std::string Key,
                                    const std::string Value);
        
        static const std::string Get_INI_Setting(std::filesystem::path INI_File, const std::string Section,
                                                 const std::string Key);

        static std::filesystem::path SetSavePath();
        
        static std::vector<std::string> Get_CSV_Column_Data(std::filesystem::path CSV_File,
                                                            const std::string Column_Name,
                                                            const uInt allocation_size);

        static mint test_csv_io();
        static mint test_ini_io();
    };
}
