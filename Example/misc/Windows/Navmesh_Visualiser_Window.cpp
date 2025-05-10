#include "Windows/All_Windows.h"
#include "3D Utils/Camera.h"
#include "Styles/custom_styles.h"


#include "raymath.h"
#include "rlgl.h"

static uInt fbo, scene_texture, depthRBO, vao, vbo;
static float clearColour[4] = { Accent_darken.x, Accent_darken.y, Accent_darken.z, 1.0f };

// Vertext shader
const char* vertexShaderSrc = R"(
#version 130
in vec3 aPos;
uniform mat4 MVP;
void main()
{
    gl_Position = MVP * vec4(aPos, 1.0);
}
)";


//frag shader
// Fragment Shader
const char* fragmentShaderSrc = R"(
#version 130
out vec4 FragColor;
void main()
{
    FragColor = vec4(0.4, 0.7, 1.0, 1.0); // Light blue
}
)";



//void init_framebuffer(ImVec2* window_size);
//void render_scene_to_framebuffer(GLuint shader, Camera*, ImVec2* viewport_size);

void InitTriangle()
{
	float vertices[] = {
		 0.0f,  0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f
	};
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}



void ImGui::NavmeshVisualiser(bool* p_open, A_LIFE::ALIFE_SCENARIO* ALIFEScenario)
{
	static Camera local_camara;
	static ImDrawListSplitter splitter;
	static bool initialised = false;
	static ImVec2 viewportSize;
	static ImVec2 prev_viewport_size = viewportSize;
	static ImGuiIO* IO_ref = &ImGui::GetIO();

	PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	Begin("Navmesh Visualiser");
	PopStyleVar();

	// TODO: This will not show due to INTEL ARC driver issues. Must make this MAIN MENU for now.
	static constexpr bool using_INTEL_GPU = true;
	if (using_INTEL_GPU ? BeginMainMenuBar() : BeginMenuBar())
	{
		if (BeginMenu("View"))
		{
			if (MenuItem("Reset View"))
				local_camara.Reset_Position();
			if (MenuItem("Toggle Debug symbols"))
				INFO("Navmesh Vis", "Peek into the Matrix Selected");

			EndMenu();
		}
		if (BeginMenu("Preferences"))
		{
			if (MenuItem("Graphics"))
				INFO("Navmesh Vis", "Graphics Selected"); // TODO: bring in graphics settiongs
			if (MenuItem("Controls"))
				INFO("Navmesh Vis", "Controls Selected"); // TODO: Have option to change control scheme

			EndMenu();
		}
		using_INTEL_GPU ? EndMainMenuBar() : EndMenuBar();
	}

	PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	viewportSize = GetContentRegionAvail();
	if (!initialised)
	{
		//init_framebuffer(&viewportSize);
		prev_viewport_size = viewportSize;
	}
	else if (viewportSize.x != prev_viewport_size.x || viewportSize.y != prev_viewport_size.y)
	{
		if (!IsMouseDown(ImGuiMouseButton_Left))
		{
			prev_viewport_size = viewportSize;
			//init_framebuffer(&viewportSize);
			INFO("Navmesh Vis", "Viewport resized to: {} x {}", prev_viewport_size.x, prev_viewport_size.y);
		}
	}

	splitter.Split(GetWindowDrawList(), 2); // Thanks https://github.com/ocornut/imgui/issues/5312

	// Render text first, however, put it to the top layer so it is rendered on top of viewport image.
	splitter.SetCurrentChannel(GetWindowDrawList(), 1);
	Text("%s", local_camara.to_string().c_str());

	ImGui::SetCursorPos(GetWindowContentRegionMin());
	splitter.SetCurrentChannel(GetWindowDrawList(), 0);
	//render_scene_to_framebuffer(&local_camara, &viewportSize);

	local_camara.onUpdate(IO_ref);
	Image((ImTextureID)scene_texture, viewportSize, ImVec2(0, 1), ImVec2(1, 0));

	PopStyleVar();

	splitter.Merge(GetWindowDrawList());

	if (!initialised)
	{
		A_LIFE::Level* DebugLevel = static_cast<A_LIFE::Level*>(A_LIFE::ALIFE_CoreObject::ObjectRegistry[*(ALIFEScenario
			->allLevels[0])]);
		if (DebugLevel->LevelMeshData.indices.empty())
		{
			DebugLevel->SetStaticMeshData(std::filesystem::current_path() / "test dungeon.obj");
		}
		SUCCESS("Navmesh Vis", "WE ABOUT TO LOAD UP A {}", *(ALIFEScenario->allLevels[0]));
		initialised = true;
	}

	ImGui::End();
}



