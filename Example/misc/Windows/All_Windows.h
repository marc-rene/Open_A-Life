#pragma once
#include <imgui.h>

struct networking_settings
{
	unsigned short listening_port;
	unsigned short sending_port;

	bool is_listening() {
		return listening_port != 0;
	}

	bool is_ready_to_send() {
		return sending_port != 0;
	}
};


namespace ImGui
{

	void Parent_Window(bool* p_open, networking_settings* nSettings);
}


