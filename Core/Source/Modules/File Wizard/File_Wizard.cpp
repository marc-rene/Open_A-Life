#include "File_Wizard.h"
#include <type_traits>
#include "Modules/Gossiper/Log.h"
#include "ThirdParty/mINI/src/mini/ini.h"
#include "ThirdParty/csv/include/csv.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <commdlg.h>
#include <cstdlib>
#include <iostream>
#include <windows.h>
typedef BOOL (WINAPI *LPFN_GLPI)(PSYSTEM_LOGICAL_PROCESSOR_INFORMATION, PDWORD);

std::unordered_map<std::string, std::string> A_LIFE::File_Wizard::Get_Environment_Vars()
{
    std::unordered_map<std::string, std::string> Info_Map;
    SYSTEM_INFO sysinfo;
    SYSTEM_INFO nativesysinfo;
    GetSystemInfo(&sysinfo);
    GetNativeSystemInfo(&nativesysinfo);

    // ---- CPU --------------------------------------------
    // Get CPU name
    int CPUInfoData[4] = {-1};
    std::vector<int> cpudata;
    char brand[0x40] = {0};
    __cpuid(CPUInfoData, 0x80000000);
    unsigned int nExIds = CPUInfoData[0];

    if (nExIds >= 0x80000004)
    {
        __cpuid((int*)CPUInfoData, 0x80000002);
        memcpy(brand, CPUInfoData, sizeof(CPUInfoData));
        __cpuid((int*)CPUInfoData, 0x80000003);
        memcpy(brand + 16, CPUInfoData, sizeof(CPUInfoData));
        __cpuid((int*)CPUInfoData, 0x80000004);
        memcpy(brand + 32, CPUInfoData, sizeof(CPUInfoData));
    }
    Info_Map["CPU Name"] = std::string(brand);

    // Get system info (cores/threads)
    SYSTEM_INFO sysInfo;
    GetSystemInfo(&sysInfo);
    Info_Map["CPU Threads"] = std::to_string(sysInfo.dwNumberOfProcessors);

    // Logical processor count with GetLogicalProcessorInformationEx
    DWORD len = 0;
    GetLogicalProcessorInformationEx(RelationProcessorCore, nullptr, &len);
    std::vector<uint8_t> buffer(len);
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX* pi = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*)&buffer[0];

    if (GetLogicalProcessorInformationEx(RelationProcessorCore, pi, &len))
    {
        int count = 0;
        char* ptr = (char*)pi;
        while (ptr < ((char*)pi + len))
        {
            auto info = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX*)ptr;
            count++;
            ptr += info->Size;
        }
        Info_Map["CPU Cores"] = std::to_string(count);
    }

    switch (nativesysinfo.wProcessorArchitecture)
    {
    case PROCESSOR_ARCHITECTURE_AMD64:
        Info_Map["CPU ARCH"] = "x64 (AMD or Intel)";
        break;
    case PROCESSOR_ARCHITECTURE_INTEL:
        Info_Map["CPU ARCH"] = "x86";
        break;
    case PROCESSOR_ARCHITECTURE_ARM:
        Info_Map["CPU ARCH"] = "ARM";
        break;
    case PROCESSOR_ARCHITECTURE_ARM64:
        Info_Map["CPU ARCH"] = "ARM64";
        break;
    case PROCESSOR_ARCHITECTURE_IA64:
        Info_Map["CPU ARCH"] = "Old as shit";
        break;
    case PROCESSOR_ARCHITECTURE_UNKNOWN:
    default:
        Info_Map["CPU ARCH"] = "Alien";
        break;
    }

    // ---- END OF CPU -------------------------------------

    // ---- RAM --------------------------------------------
    MEMORYSTATUSEX memStatus;
    memStatus.dwLength = sizeof(memStatus);

    if (GlobalMemoryStatusEx(&memStatus))
    {
        Info_Map["RAM Total Ammount"] = std::format("{} MB", memStatus.ullTotalPhys / (1024 * 1024));
        Info_Map["RAM Total Available"] = std::format("{} MB", memStatus.ullAvailPhys / (1024 * 1024));
    }
    // ---- END OF RAM -------------------------------------

    // ---- STORAGE ----------------------------------------
    ULARGE_INTEGER freeBytesAvailable, totalBytes, totalFreeBytes;

    if (GetDiskFreeSpaceExW(L".", &freeBytesAvailable, &totalBytes, &totalFreeBytes))
    {
        Info_Map["Storage Total"] = std::format("{} GB",totalBytes.QuadPart / (1024 * 1024 * 1024));
        Info_Map["Storage Free"] = std::format("{} GB", totalFreeBytes.QuadPart / (1024 * 1024 * 1024));
    }
    // ---- END OF STORAGE ---------------------------------


    LPFN_GLPI glpi = (LPFN_GLPI) GetProcAddress(GetModuleHandle(TEXT("kernel32")), "GetLogicalProcessorInformation");
    DWORD buffer_bytes = 0;
    int cache_size = 0;

    glpi(0, &buffer_bytes);
    std::size_t size = buffer_bytes / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
    SYSTEM_LOGICAL_PROCESSOR_INFORMATION* cachebuffer = new SYSTEM_LOGICAL_PROCESSOR_INFORMATION[size];
    glpi(cachebuffer, &buffer_bytes);

    for (std::size_t i = 0; i < size; i++)
    {
        if (cachebuffer[i].Relationship == RelationCache &&
            cachebuffer[i].Cache.Level == 1)
        {
            cache_size = (int) cachebuffer[i].Cache.Size;
            break;
        }
    }

    delete cachebuffer;
    
    Info_Map["CPU L1 Per-Core Cache Size"] = std::format("{} KB", cache_size);
    return Info_Map;
}
#else
// Linux Code here
#endif


#include <exception>
#include <fstream>
#include <iostream>
#include "csv.hpp"
#include "string"
#include "array"
#include <stdlib.h>
#include <map>
#include <mutex>


namespace A_LIFE
{
    /*
    static std::unordered_map<std::string, dir_path> OAL_Folders
    {
        {"Settings Folder", dir_path("Settings")},
        {"Data Folder", dir_path("Data")}
    };
    static bool			Init_Required = true;

    static dir_path*	Settings_Folder_Ref = &OAL_Folders["Settings Folder"];
    static dir_path*	Data_Folder_Ref = &OAL_Folders["Data Folder"];

    static std::string	Core_Settings_File_Name = "OAL Core Settings.ini";

    static std::mutex	Settings_File_Mutex;
    static std::mutex	OAL_Folders_Mutex;


    void		File_Wizard::List_Environment_Vars()
    {
        mutex_lock folder_lock(OAL_Folders_Mutex);

        INFOc("Current Working Directory is {}", std::filesystem::current_path().string());

        for (auto& folder : OAL_Folders)
        {
            if (std::filesystem::is_directory(folder.second))
                INFOc("{} is : {}", folder.first, folder.second.string());

            else
                ERRORc("NO VALID FOLDER FOR {} IS SET!", folder.second.string());
        }
    }

    mint		File_Wizard::Init(bool create_folders_immidiatly)
    {
        if (Init_Required == false)
        {
            WARNc("File Wizard has already been initialised, Ignoring...");
            return 0;
        }
        try
        {
            mutex_lock OAL_Folder_lock(OAL_Folders_Mutex);
            mutex_lock Settings_lock(Settings_File_Mutex);

            for (auto& folder : OAL_Folders)
            {
                if (std::filesystem::is_directory(folder.second) && std::filesystem::exists(folder.second))
                    INFOc("{} folder already exists", folder.first);
                else
                    if (create_folders_immidiatly)
                        std::filesystem::create_directory(folder.second);
            }

            // Do we have our Settings File ???
            file_path temp_settings_path = file_path(*Settings_Folder_Ref / Core_Settings_File_Name);
            if (std::filesystem::exists(temp_settings_path.string()) == false)	// Does't exist
            {
                WARNc("No {} File found in {} folder... Creating one now", Core_Settings_File_Name, Settings_Folder_Ref->string());
                std::ofstream OAL_Core_Settings = std::ofstream(temp_settings_path);

                OAL_Core_Settings << "------------------------------------------------------" << std::endl;
                OAL_Core_Settings << "Copyright : Coming soon...                            " << std::endl;
                OAL_Core_Settings << "------------------------------------------------------" << std::endl;
                OAL_Core_Settings << "                                                      " << std::endl;

                OAL_Core_Settings.close();
            }

            settings_ini_file = mINI::INIFile(temp_settings_path.string());
            settings_ini_file.read(settings_struct);


            //Now we check if we have data to work with
            if (std::filesystem::exists(*Data_Folder_Ref) == false)
            {
                WARNc("{} doesn't exist, creating it now");
                mkdir(Data_Folder_Ref->string().c_str());
            }

            Init_Required = false;
            return 0;
        }
        catch (const std::exception& ex)
        {
            ERRORc("ERROR WHEN INITIALISING FILE WIZARD : {}", ex.what());
            return 1;
        }
    }

    mint		File_Wizard::Set_Folder_Path(std::string folder_to_edit, dir_path new_path)
    {
        bool valid_key = false;

        std::lock_guard<std::mutex> lock(OAL_Folders_Mutex);

        // Did you enter the right Key??
        for (auto& key : OAL_Folders)
        {
            //TODO : LOWERCASE the strings first
            std::string folder_to_edit_lower = folder_to_edit;
            std::string key_lower = key.first;

            for (auto& c : folder_to_edit_lower)
                c = tolower(c);

            for (auto& c : key_lower)
                c = tolower(c);

            if (folder_to_edit_lower.compare(key_lower) == 0)
            {
                valid_key = true;
                key.second = new_path;
                INFOc("{} now set to {}", folder_to_edit, new_path.string());
                Init_Required = true;
                Init(true);
                return 0; // unlocks OAL Folder Mutex
            }
        }

        WARNc("HEY! {} ain't a valid key! Pain in my Asshole ", folder_to_edit);
        return 1;
    }

    
    
    bool		File_Wizard::Set_Setting(std::string Section, std::string Key, std::string Value)
    {
        mutex_lock setting_lock(Settings_File_Mutex);

        settings_ini_file.read(settings_struct);
        settings_struct[Section][Key] = Value;
        
        return settings_ini_file.write(settings_struct);
    }

    

    

    mint		File_Wizard::Transfer_Folder_Content(dir_path source_folder, dir_path target_folder)
    {
        // TODO : Fill this out with iterator
        return 1;
    }

}



// Overloads
namespace Core
{
    std::vector<std::string> File_Wizard::Get_CSV_Column_Data(const char* CSV_File, const char* Column_Name, const unsigned int allocation_size)
    {
        return Get_CSV_Column_Data(file_path(CSV_File), Column_Name, allocation_size);
    }
}

// Testing
namespace Core
{
    mint File_Wizard::test_csv_io()
    {
        INFOc("Testing CSV file IO");

        try
        {
            TIMER_START;
            const char* test_file_name = "Test CSV Check.csv";
            std::ofstream test_file = std::ofstream(test_file_name);

            test_file << "\"c1\",\"c2\",\"c3\"\n\"c1d0\",\"c2d0\",\"c3d0\"\n\"c1d1\",\"c2d1\",\"c3d1\"\n\"c1d2\",\"c2d2\",\"c3d2\"";

            test_file.close();

            csv::CSVReader reader(test_file_name);

            std::array<std::string, 3> test_array;


            for (int index = 0; auto & row : reader) { // Input iterator

                test_array[index] = row["c2"].get<std::string>();
                index++;
            }

            if (test_array[0] == "c2d0")
            {
                SUCCESSc("CSV Test 1/3 passed");
            }
            else { throw std::runtime_error("CSV Parse Test Failed"); }

            if (test_array[1] == "c2d1")
            {
                SUCCESSc("CSV Test 2/3 passed");
            }
            else { throw std::runtime_error("CSV Parse Test Failed"); }

            if (test_array[2] == "c2d2")
            {
                SUCCESSc("CSV Test 3/3 passed");
            }
            else { throw std::runtime_error("CSV Parse Test Failed"); }


            std::remove(test_file_name);
            TIMER_ELAPSEDc("CSV Test passed in {:.4} seconds, GREAT SUCCESS");
        }

        catch (std::exception& ex)
        {
            ERRORc("ERROR : CSV Failed test {}", ex.what());
            return 1;
        }

        return 0;

    }

    mint File_Wizard::test_ini_io()
    {
        try
        {
            TIMER_START;
            const char* test_file_name = "Test INI check.ini";

            // create a file instance
            mINI::INIFile ini_file(test_file_name);

            // create a data structure
            mINI::INIStructure ini_structure;

            // populate the structure
            ini_structure["test"]["Value 1"] = "20";
            ini_structure["test"]["Value 2"] = "100";
            ini_structure["2nd Section"]["Value 3"] = "43";

            // generate an INI file (overwrites any previous file)
            ini_file.generate(ini_structure, true);

            std::string temp_read = ini_structure.get("test").get("VaLuE 1");

            // Test 1 - Getting values succeeds?
            if (ini_structure.get("test").has("Value 1") == true && temp_read.compare("20") == 0)
            {
                SUCCESSc("INI Test 1/3 passed");
            }
            else { throw std::runtime_error("INI Parse Test Failed"); }

            // Test 2 - Does the "has" method work?
            if (ini_structure.get("test").has("Value 3") == false && ini_structure.get("2nd sEcTiOn").has("Value 3") == true)
            {
                SUCCESSc("INI Test 2/3 passed");
            }
            else {

                throw std::runtime_error(std::format("value 3 of test section returned {} and value 3 of 2nd section returned {}", ini_structure.get("test").has("Value 3"), ini_structure.get("2nd sEcTiOn").has("Value 3")));
            }

            // Test 3 - Does INI update work?
            ini_structure["TeSt"]["vAlUe 2"] = "9999";
            if (ini_structure.get("test").get("Value 2").compare("9999") == 0)
            {
                SUCCESSc("INI Test 3/3 passed");
            }
            else { throw std::runtime_error("INI Parse Test Failed"); }

            TIMER_ELAPSEDc("INI Test passed in {:.4} seconds, GREAT SUCCESS");

            std::remove(test_file_name);
        }
        catch (const std::exception& ex)
        {
            ERRORc("ERROR : INI Failed test {}", ex.what());
            return 1;
        }

        return 0;
    }

    std::string Get_Setting(const std::string Section, const std::string Key)
    {
        settings_ini_file.read(settings_struct);

        INFOc("Value for {} is {} ", Key, settings_struct.get(Section).get(Key));

        if (settings_struct[Section].has(Key))
            return settings_struct[Section][Key];

        else
        {
            WARNc("{} is NOT in the {} section in Settings file", Key, Section);
            return "N/A";
        }
    }
*/

    template <typename T>
    std::vector<T> Get_CSV_Column_Data(std::filesystem::path CSV_File, const std::string Column_Name,
                                       const unsigned int allocation_size = 1024)
    {
        // Step 1 : Check and see if this file even exists and isn't empty??
        if (std::filesystem::exists(CSV_File) && !std::filesystem::is_empty(CSV_File))
            INFO("File Wizard", "We're starting to read {} now", CSV_File.string());
        else
        {
            WARN("File Wizard", "HEY! {} doesn't exist", CSV_File.string());
            return {};
        }

        // mINI has specific field getters for certain types
        if constexpr ((std::is_same_v<T, std::string>
            || std::is_same_v<T, std::wstring>
            || std::is_same_v<T, int>
            || std::is_same_v<T, float>
            || std::is_same_v<T, double>
            || std::is_same_v<T, long double>) == false)
        {
            WARN("File Wizard", "We can't parse {} type values from {}", typeid(T).name(), CSV_File.string());
            return {};
        }

        // Step 2 : Awesome lets get it
        csv::CSVReader reader(CSV_File.string());

        std::vector<std::string> entries_buffer(allocation_size);

        for (csv::CSVRow& row : reader)
        {
            entries_buffer.push_back(row[Column_Name].get<T>());
        }

        entries_buffer.shrink_to_fit();

        return entries_buffer;
    }

    std::filesystem::path SetSavePath()
    {
        char szFile[MAX_PATH] = {0};

        OPENFILENAMEA ofn = {0};
        ofn.lStructSize = sizeof(OPENFILENAMEA);
        ofn.lpstrFile = szFile;
        ofn.nMaxFile = sizeof(szFile);
        ofn.lpstrFilter = "Scenario Files (*.scenario)\0*.scenario\0All Files (*.*)\0*.*\0";
        ofn.nFilterIndex = 1;
        ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
        ofn.lpstrDefExt = "scenario";
        ofn.lpTemplateName = "Salut maman";
        ofn.lpstrTitle = "Habibi, where we save our new Scenario?";

        // Q: WHY NOT USE COMMON ITEM DIALOG??
        // A: I am a lazy man, I am an unwise man, and most of all, I am a man still awake at 3:28am
        //    I am unable to motivate myself to figure out how CID works...

        //TODO: Saw weird bug, chosen save location results in the Logs being written to that folder, wtf?
        if (GetSaveFileNameA(&ofn))
        {
            return std::filesystem::path(ofn.lpstrFile);
        }
        else
        {
            // User cancelled or an error occurred
            return std::filesystem::current_path() / "Nouveau Scenario.scenario";
        }
    }


    std::string File_Wizard::List_Environment_Vars(const char delimiter)
    {
        auto system_info = Get_Environment_Vars();
        std::string buffer = "";

        for (auto const& [key, value] : system_info)
        {
            buffer.append(std::format("{}: {}\n", key, value));
        }

        return buffer;
    }
}
