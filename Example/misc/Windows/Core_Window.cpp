#include "Windows/All_Windows.h"
#include "Styles/custom_styles.h"

void ImGui::Core_Window(Core::OPEN_ALIFE_CORE* core) {
	ImGui::Begin("Core Logger");

	ImGui::Text("Hello from %d", core->UID);
	ImGui::End();
}