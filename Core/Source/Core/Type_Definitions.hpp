#pragma once

#include <filesystem>
#include <unordered_map>
#include <map>

#define file_path std::filesystem::path()
#define mint		__int8      // "Mini" integer
#define uMint		uint8_t
#define short		__int16     // Ensure all shorts are the same, regardless of compiler
#define uShort		uint16_t    
#define int         __int32     
#define uInt		uint32_t
#define fatty 		__int64     // BIG
#define uFatty 		uint64_t     
#define mutex_lock	std::lock_guard<std::mutex>
#define BIT(x)		(1 << x)

#define ASYNC_MODE std::launch::async

#define LOCAL_ALIFE_VERSION A_LIFE_Version(1,0,0,"Pre-Beta")

struct A_LIFE_Version
{
    
    uMint major;
    uMint minor;
    uMint patch;
    std::string version_nickname;

    A_LIFE_Version(uMint maj = 0, uMint min = 0, uMint pat = 0, std::string nickname = "Borat Edition")
    {
        major = maj;
        minor = min;
        patch = pat;
        version_nickname = nickname;
    }
    
    /// 
    /// @param versionString The Alife Version in the format 'X.Y.Z' 
    /// @return the same version but in ALIFE_Version struct
    static A_LIFE_Version from_string(const std::string& versionString)
    {
        uMint majDot = static_cast<uMint>(versionString.find('.'));
        uMint minDot = static_cast<uMint>(versionString.find('.', majDot + 1));

        if (majDot == std::string::npos || minDot == std::string::npos)
        {
            // ALIFE Versioning must be in the format 'X.Y.Z'... you done fucked up
            return A_LIFE_Version{0,0,0};
        }


        std::string majStr = versionString.substr(0, majDot);
        std::string minStr = versionString.substr(majDot + 1, minDot - majDot - 1);
        std::string patStr = versionString.substr(minDot + 1);

        uMint maj = std::stoi(majStr);
        uMint min = std::stoi(minStr);
        uMint pat = std::stoi(patStr);

        if (maj < 0 || maj > 255 ||
            min < 0 || min > 255 ||
            pat < 0 || pat > 255)
        {
            // Version numbers must fit in uMint range (0-255), You done fucked up
            return A_LIFE_Version{0,0,0};
        }

        return A_LIFE_Version(maj, min, pat);
    }

    bool is_valid()
    {
        return !(major == 0 && minor == 0 && patch == 0);
    }

    std::string to_string()
    {
        return std::format("{}.{}.{}", major, minor, patch);
    }

    std::string full_title()
    {
        return std::format("ALIFE Version {}.{}.{} \"{}\"", major, minor, patch, version_nickname);
    }

    std::string full_title_NT()
    {
        return std::format("{}.{}.{} \"{}\"", major, minor, patch, version_nickname);
    }

    /// 
    /// @param other Which ALIFE version are we checking?  
    /// @return We have the SAME patch
    bool is_exactly_same(const A_LIFE_Version& other)
    {
        return major == other.major && minor == other.minor && patch == other.patch;
    }

    /// 
    /// @param other Which ALIFE Version we checking?
    /// @return We dont care about the patch
    bool is_minor_same(const A_LIFE_Version& other) const
    {
        return major == other.major && minor == other.minor;
    }

    bool is_major_same(const A_LIFE_Version& other) const
    {
        return major == other.major;
    }

    bool operator ==(const A_LIFE_Version& other) const
    {
        return major == other.major && minor == other.minor && patch == other.patch;
    }


    bool operator <(const A_LIFE_Version& other) const
    {
        if (major != other.major)
            return major < other.major;

        else if (minor != other.minor)
            return minor < other.minor;

        return patch < other.patch;
    }

    bool operator !=(const A_LIFE_Version& other) const { return !(*this == other); }
    bool operator >(const A_LIFE_Version& other) const { return (other < *this); }
    bool operator <=(const A_LIFE_Version& other) const { return (*this < other) || (*this == other); }
    bool operator >=(const A_LIFE_Version& other) const { return (other < *this) || (*this == other); }
};


enum ELogLevel : uMint
{
    Verbose = BIT(0), // ...
    Info = BIT(1), // Oh ok...
    Warning = BIT(2), // Oh my!
    Error = BIT(3) // OH SHIT!
};


// Sets flag to true
static void set_flag(uMint* BitFlagDst, uMint new_flag)
{
    *BitFlagDst |= (uMint)new_flag;
}

#define add_flag set_flag

// Sets flag to false
static void remove_flag(uMint* BitFlagDst, uMint removing_flag)
{
    *BitFlagDst &= ~(uMint)removing_flag;
}

// Sets a flag value from true to false and vice versa
static void flip_flag(uMint* BitFlagDst, uMint flag_to_flip)
{
    *BitFlagDst ^= (uMint)flag_to_flip;
}

// Check whether a flag is set to true
static bool has_flag(uMint* BitFlagDst, uMint flag_to_check)
{
    return (*BitFlagDst & (uMint)flag_to_check) == (uMint)flag_to_check;
}

static bool has_any_flags(uMint* BitFlagDst, uMint all_flags)
{
    return (*BitFlagDst & (uMint)all_flags) != 0;
}
