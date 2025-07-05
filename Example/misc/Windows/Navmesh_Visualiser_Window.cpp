#include "Windows/All_Windows.h"
#include "3D Utils/Camera.h"
#include "Styles/custom_styles.h"

#include "TinyOBJ/tiny_obj_loader.h"
#include "raymath.h"




#include "rlgl.h"

static uInt vao = 0, vbo = 0, shaderProgram = 0;
static uInt fbo = 0, colorTexture = 0, depthRBO = 0;

static const char* Window_Title = "Navmesh Visualiser";



void ImGui::NavmeshVisualiser(bool* p_open, A_LIFE::ALIFE_SCENARIO* ALIFEScenario)
{
	static Camera local_camera;
	static bool initialised = false;
	static ImVec2 prevViewportSize;
	static ImGuiIO* IO_ref = &ImGui::GetIO();
	static ImDrawListSplitter splitter;
	static ImVec4* bg_colour = &ImGui::GetStyle().Colors[ImGuiCol_WindowBg];


	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin(Window_Title, p_open);
	ImGui::PopStyleVar();

    if (!initialised)
    {
       
        prevViewportSize = ImGui::GetContentRegionAvail();
    }
    
	// TODO: This will not show due to INTEL ARC driver issues. Must make this MAIN MENU for now.
	static constexpr bool using_INTEL_GPU = true;
	if (using_INTEL_GPU ? BeginMainMenuBar() : BeginMenuBar())
	{
		if (BeginMenu("View"))
		{
			if (MenuItem("Reset View"))
				local_camera.Reset_Position();
			if (MenuItem("Toggle Debug symbols"))
				INFO(Window_Title, "Peek into the Matrix Selected");

			EndMenu();
		}
		if (BeginMenu("Preferences"))
		{
			if (MenuItem("Graphics"))
				INFO(Window_Title, "Graphics Selected"); // TODO: bring in graphics settiongs
			if (MenuItem("Controls"))
				INFO(Window_Title, "Controls Selected"); // TODO: Have option to change control scheme

			EndMenu();
		}
		using_INTEL_GPU ? EndMainMenuBar() : EndMenuBar();
	}


	// Update camera
	local_camera.onUpdate(&ImGui::GetIO());

	// Render scene to Framebuffer
	//lBindFramebuffer(GL_FRAMEBUFFER, fbo);

	//glClearColor(bg_colour->x, bg_colour->y, bg_colour->z, bg_colour->w);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//TODO: Learn about Opengl and graphics LATER, DirectX killed me
	//glDrawElements(GL_LINES, TESTgrid_length, GL_UNSIGNED_INT, NULL);


	// The end
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);




	// Render text first, however, put it to the top layer so it is rendered on top of viewport image.
	splitter.Split(GetWindowDrawList(), 2); // Thanks https://github.com/ocornut/imgui/issues/5312
	splitter.SetCurrentChannel(GetWindowDrawList(), 0);
	ImGui::Image((ImTextureID)colorTexture, prevViewportSize, ImVec2(0, 1), ImVec2(1, 0));

	local_camera.onUpdate(IO_ref);
	ImGui::SetCursorPos(GetWindowContentRegionMin());

	splitter.SetCurrentChannel(GetWindowDrawList(), 1);
	Text("%s", local_camera.to_string().c_str());


	splitter.Merge(GetWindowDrawList());

	ImGui::End();
}
