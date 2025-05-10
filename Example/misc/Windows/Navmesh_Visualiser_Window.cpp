#include "Windows/All_Windows.h"
#include "3D Utils/Camera.h"
#include "Styles/custom_styles.h"


#include "raymath.h"
#include "rlgl.h"


void ImGui::NavmeshVisualiser(bool* p_open, A_LIFE::ALIFE_SCENARIO* ALIFEScenario)
{
	static Camera local_camera;
	static GLuint fbo = 0, colorTexture = 0, depthRBO = 0;
	static GLuint vao = 0, vbo = 0, shaderProgram = 0;
	static bool initialized = false;
	static ImVec2 viewportSize;
	static ImGuiIO* IO_ref = &ImGui::GetIO();
	static ImDrawListSplitter splitter;



	auto InitGLResources = [](int width, int height)
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

			// Triangle Mesh
			float vertices[] = {0,0,0,
				0,1,0,
				1,1,0,
				1,0,0
			};
			glGenVertexArrays(1, &vao);
			glGenBuffers(1, &vbo);
			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

			// Shader
			const char* vsSrc = R"(
            #version 130
            in vec3 aPos;
            uniform mat4 MVP;
            void main() { gl_Position = MVP * vec4(aPos, 1.0); }
        )";

			const char* fsSrc = R"(
            #version 130
            out vec4 FragColor;
            void main() { FragColor = vec4(0.4, 0.7, 1.0, 1.0); }
        )";

			auto CompileShader = [](const char* src, GLenum type) {
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
		};

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin("Navmesh Visualiser", p_open);
	ImGui::PopStyleVar();

	// TODO: This will not show due to INTEL ARC driver issues. Must make this MAIN MENU for now.
	static constexpr bool using_INTEL_GPU = true;
	if (using_INTEL_GPU ? BeginMainMenuBar() : BeginMenuBar())
	{
		if (BeginMenu("View"))
		{
			if (MenuItem("Reset View"))
				local_camera.Reset_Position();
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

	viewportSize = ImGui::GetContentRegionAvail();
	int width = static_cast<int>(viewportSize.x);
	int height = static_cast<int>(viewportSize.y);

	if (!initialized)
	{
		InitGLResources(width, height);
		initialized = true;
	}

	// Render scene to FBO
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Matrix view = local_camera.GetViewMatrix();
	Matrix proj = MatrixPerspective(45.0f * DEG2RAD, (float)width / height, 0.1f, 1000.0f);
	Matrix mvp = MatrixMultiply(view, proj);

	glUseProgram(shaderProgram);
	GLint mvpLoc = glGetUniformLocation(shaderProgram, "MVP");
	glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, (float*)&mvp);

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	splitter.Split(GetWindowDrawList(), 2); // Thanks https://github.com/ocornut/imgui/issues/5312

	// Render text first, however, put it to the top layer so it is rendered on top of viewport image.
	glMatrixMode(GL_PROJECTION);
	splitter.SetCurrentChannel(GetWindowDrawList(), 0);
	ImGui::Image((ImTextureID)colorTexture, viewportSize);
	
	local_camera.onUpdate(IO_ref);
	ImGui::SetCursorPos(GetWindowContentRegionMin());
	
	splitter.SetCurrentChannel(GetWindowDrawList(), 1);
	Text("%s", local_camera.to_string().c_str());


	splitter.Merge(GetWindowDrawList());

	ImGui::End();
}



