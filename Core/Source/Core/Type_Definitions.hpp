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

enum EState
{
	// Send to Frontend
	CRITICAL_FAILURE	= 1 << 0,	//	00000001
	TURNING_OFF			= 1 << 1,	//	00000010
	
	// For recieve
	HIGH_POWER_MODE		= 1 << 2,	//	00000100	// Ignore power restrictions
	LOW_POWER_MODE		= 1 << 3,	//	00001000	// Follow power restrictions 
	RESET_FROM_FILE		= 1 << 4,	//	00010000	// Reset simulation from a pre-defined "save point"
	PAUSE				= 1 << 5,	//	00100000	// Pause until messaged recieved to continue

	// Coming soon
	__nothing__yet_1	= 1 << 6,	//	01000000	
	__nothing__yet_2	= 1 << 7	//	10000000	
};


//Sets flag to true
static void set_flag(uMint* BitFlagDst, uMint new_flag)
{
	*BitFlagDst |= (uMint)new_flag;
}

//Sets flag to false
static void remove_flag(uMint* BitFlagDst, uMint removing_flag)
{
	*BitFlagDst &= ~(uMint)removing_flag;
}

//Sets a flag value from true to false and vice versa
static void flip_flag(uMint* BitFlagDst, uMint flag_to_flip)
{
	*BitFlagDst ^= (uMint)flag_to_flip;
}

//Check whether a flag is set to true
static bool has_flag(uMint* BitFlagDst, uMint flag_to_check)
{
	return (*BitFlagDst & (uMint)flag_to_check) == (uMint)flag_to_check;
}

static bool has_any_flags(uMint* BitFlagDst, uMint all_flags)
{
	return (*BitFlagDst & (uMint)all_flags) != 0;
}

