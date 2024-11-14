#include "Tests.h"
#include "assert.h"

bool Tests::test_type_definitions_flag_functionality()
{
	EState test_flag;

	printf("Starting Tests for Bit Flags Functionality");
	
	//Set flag
    set_flag((uMint*)&test_flag, (uMint)EState::CRITICAL_FAILURE); 
    assert(has_flag((uMint*)&test_flag, (uMint)EState::CRITICAL_FAILURE));

    //Unset flag
    remove_flag((uMint*)&test_flag, (uMint)EState::CRITICAL_FAILURE); 
    assert(!has_flag((uMint*)&test_flag, (uMint)EState::CRITICAL_FAILURE));

    //Set multiple flags at once
    
    set_flag((EFlagValue)((int)EFlagValue::Flag1 | (int)EFlagValue::Flag2)); //Flag = 3 (00000011)
    assert(flag.HasFlag(EFlagValue::Flag1));
    assert(flag.HasFlag(EFlagValue::Flag2));
    assert(flag.HasFlag((EFlagValue)((int)EFlagValue::Flag1 | (int)EFlagValue::Flag2)));
    assert(!flag.HasFlag((EFlagValue)((int)EFlagValue::Flag1 | (int)EFlagValue::Flag4)));
    assert(flag.HasAnyFlag((EFlagValue)((int)EFlagValue::Flag1 | (int)EFlagValue::Flag4)));

    //Flip flag 4 from 0 to 1
    flag.FlipFlag(EFlagValue::Flag4); //Flag = 11 (00001011)
    assert(flag.HasFlag(EFlagValue::Flag4));

    //Flip flag 2 from 1 to 0
    flag.FlipFlag(EFlagValue::Flag2); //Flag = 9 (00001001)
    assert(!flag.HasFlag(EFlagValue::Flag2));
    */
	return true;
}