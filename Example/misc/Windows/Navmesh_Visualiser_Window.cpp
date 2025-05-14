#include "Windows/All_Windows.h"
#include "3D Utils/Camera.h"
#include "Styles/custom_styles.h"

#include "TinyOBJ/tiny_obj_loader.h"
#include "raymath.h"




#include "rlgl.h"

static uInt vao = 0, vbo = 0, shaderProgram = 0;
static uInt fbo = 0, colorTexture = 0, depthRBO = 0;

static const char* Window_Title = "Navmesh Visualiser";


/*
void InitGLResources(int width, int height)
{
	// FBO
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &colorTexture);
	glBindTexture(GL_TEXTURE_2D, colorTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);

	glGenRenderbuffers(1, &depthRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, depthRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthRBO);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		ERRORc("Framebuffer not complete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// Shader
	const char* vsSrc = R"(#version 330 core
		layout(location = 0) in vec3 aPos;
		uniform mat4 model;
		uniform mat4 view;
		uniform mat4 projection;
		void main() {
			gl_Position = projection * view * model * vec4(aPos, 1.0);
		})";

	const char* fsSrc = R"(
            #version 330
            out vec4 FragColor;
            void main() { FragColor = vec4(0.4, 0.7, 1.0, 1.0); }
        )";

	auto CompileShader = [](const char* src, GLenum type)
		{
			GLuint shader = glCreateShader(type);
			glShaderSource(shader, 1, &src, nullptr);
			glCompileShader(shader);
			return shader;
		};

	GLuint vs = CompileShader(vsSrc, GL_VERTEX_SHADER);
	GLuint fs = CompileShader(fsSrc, GL_FRAGMENT_SHADER);
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vs);
	glAttachShader(shaderProgram, fs);
	glLinkProgram(shaderProgram);
	glDeleteShader(vs);
	glDeleteShader(fs);
}

*/
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
