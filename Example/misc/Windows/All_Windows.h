#pragma once
#include <imgui.h>
#include "Open_ALife.h"




namespace ImGui
{
	void Core_Window(ALIFE_SCENARIO* Core_ref);
	void Parent_Window(bool* p_open);
	void Test_Window(bool* p_open);
}


