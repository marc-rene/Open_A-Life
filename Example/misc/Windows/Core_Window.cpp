#include "Windows/All_Windows.h"
#include "Styles/custom_styles.h"

void ImGui::Core_Window(Core::OPEN_ALIFE* core) {
	ImGui::Begin("Core Logger");

	ImGui::Text("Hello from %d");
	ImGui::End();
}