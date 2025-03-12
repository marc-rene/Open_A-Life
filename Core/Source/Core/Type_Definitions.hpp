#pragma once

#include <filesystem>

#define mint		__int8
#define uMint		uint8_t
#define short		__int16
#define uShort		uint16_t
#define file_path	std::filesystem::path
#define dir_path	std::filesystem::path
#define mutex_lock	std::lock_guard<std::mutex>
#define BIT(x)		(1 << x)

#define ASYNC_MODE std::launch::async

enum ELogLevel : uMint
{
	Verbose = BIT(0),	// ...
	Info = BIT(1),		// Oh ok...
	Warning = BIT(2),	// Oh my!
	Error	= BIT(3)	// OH SHIT!
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

