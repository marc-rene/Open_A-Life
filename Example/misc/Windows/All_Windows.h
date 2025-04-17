#pragma once
#include <imgui.h>
#include "Open_ALife.h"




namespace ImGui
{
	void Core_Window(A_LIFE::ALIFE_SCENARIO* Core_ref);
	void Parent_Window(bool* p_open = NULL);
	void Test_Window(bool* p_open = NULL);
	void Scenario_Maker_Window(bool* p_open = NULL);
}


