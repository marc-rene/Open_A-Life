#pragma once

#include <filesystem>

#define mint		__int8
#define uMint		unsigned __int8
#define file_path	std::filesystem::path
#define dir_path	std::filesystem::path
#define mutex_lock	std::lock_guard<std::mutex>
#define BIT(x)		(1 << x)

enum class EState : uint8_t
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

struct StateFlag
{
	//Sets flag to true
	void set_flag(EState flag)
	{
		Flag_Value |= (uint8_t)flag;
	}

	//Sets flag to false
	void remove_flag(EState flag)
	{
		Flag_Value &= ~(uint8_t)flag;
	}

	//Sets a flag value from true to false and vice versa
	void flip_flag(EState flag)
	{
		Flag_Value ^= (uint8_t)flag;
	}

	//Check whether a flag is set to true
	bool has_flag(EState flag)
	{
		return (Flag_Value & (uint8_t)flag) == (uint8_t)flag;
	}

	bool has_any_flags(EState multiFlag)
	{
		return (Flag_Value & (uint8_t)multiFlag) != 0;
	}

	uint8_t Flag_Value = 0;
};