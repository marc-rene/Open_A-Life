#include "Windows/All_Windows.h"
#include <format>
#include <future>
#include <Windows.h>


// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
    ERRORc("GLFW Error {}: {}", error, description)
}

// Forward declarations of helper functions
void CheckSystemColourScheme(bool*, std::thread::id, bool*, bool*);


// Create Our Window
int CreateAppWindow(A_LIFE::ALIFE_SCENARIO* ALIFE_CORE)
{
    // Create application window
    //ImGui_ImplWin32_EnableDpiAwareness();
    //------------------------------------
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window with graphics context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Open A-Life Visualisation Tool", nullptr, nullptr);
    if (window == nullptr)
    {
        ERRORc("{} WE CANT MAKE A DAMN OPENGL WINDOW! FAILURE!!!!", FAILURE_msg);
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    //{
    //    ERRORc("{} Failed to initialize GLAD", FAILURE_msg);
    //    return -1;
    //}
    //------------------------------------ 


    bool done = false;
    bool use_dark_mode = true;
    bool force_colour_scheme = false; // Use system colour scheme

    /*--- DEBUGGING PURPOSES ------------------------*/
    bool xShowDemoWindow = true;
    /*-----------------------------------------------*/

    /*--- WHAT WINDOWS TO SHOW ----------------------*/
    bool showScenarioMaker = false;
    bool showNavmeshVisualiser = false;
    /*-----------------------------------------------*/

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos; // Enable Multi-Viewport / Platform Windows
    io.ConfigFlags |= ImGuiButtonFlags_AllowOverlap;
    io.ConfigFlags |= ImGuiHoveredFlags_AllowWhenOverlappedByItem;
    io.ConfigWindowsMoveFromTitleBarOnly = true;
    io.ConfigDockingWithShift = true;
    io.ConfigDockingTransparentPayload = true;
    io.ConfigViewportsNoTaskBarIcon = false;
    io.ConfigViewportsNoDecoration = true;

    // Setup Dear ImGui style
    ImGui::SetStyleMode(nullptr, use_dark_mode);


#if WINDOWS
    // Make a new thread that will check if we need to switch styles
    std::future<void> DarkModeCheckThread = std::async(std::launch::async, CheckSystemColourScheme, &done,
                                                       std::this_thread::get_id(), &force_colour_scheme,
                                                       &use_dark_mode);
#endif

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.3f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);


    // Load Fonts
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("misc\\Fonts\\static\\OpenSans-Regular.ttf", 18);
    io.Fonts->AddFontFromFileTTF("misc\\Fonts\\static\\OpenSans-Light.ttf", 18);
    io.Fonts->AddFontFromFileTTF("misc\\Fonts\\static\\OpenSans-Regular.ttf", 22);
    io.Fonts->AddFontFromFileTTF("misc\\Fonts\\static\\OpenSans-Bold.ttf", 11);
    io.Fonts->Build();

    // Our state
    ImVec4 clear_color = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];

    // Main loop

    while (!done)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Main Menu Bar
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New Scenario", nullptr, &showScenarioMaker, true))
                {
                }
                if (ImGui::MenuItem("Open Scenario"))
                {
                    /* COMING SOON */
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Autosave", nullptr, true, true))
                {
                    /* COMING SOON */
                }
                if (ImGui::MenuItem("Save", "CTRL+S"))
                {
                    /* COMING SOON */
                }
                if (ImGui::MenuItem("Save As"))
                {
                    /* COMING SOON */
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Exit")) { done = true; }

                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("DEBUG"))
            {
                if (ImGui::MenuItem("DEMO WINDOW", nullptr, &xShowDemoWindow, true))
                {
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View"))
            {
                if (ImGui::MenuItem("Force Dark Mode", nullptr, &force_colour_scheme, true))
                {
                    if (force_colour_scheme == true)
                    {
                        use_dark_mode = true;
                    }
                }
                ImGui::EndMenu();
            }
        }
        ImGui::EndMainMenuBar();


        ImGui::Parent_Window(&done);

        if (xShowDemoWindow)
            ImGui::ShowDemoWindow();

        // Let all logs go to terminal instead
        // ImGui::Core_Window(ALIFE_CORE);
        // Scenario_Maker_Window mutates its bool,
        if (showScenarioMaker)
            ImGui::Scenario_Maker_Window(&showScenarioMaker); 
        
        // ...you have been warned
        // This is becuase a widget cannot suicide itself
        if(showNavmeshVisualiser)
            ImGui::OBJ_Viewer_Window(&showNavmeshVisualiser);

        clear_color = ImGui::GetStyle().Colors[ImGuiCol_WindowBg];


        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        //glViewport(0, 0, display_w, display_h);
        //glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
        //             clear_color.w);
        //glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(window);
        done = glfwWindowShouldClose(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}


// Helper functions
void CheckSystemColourScheme(bool* done, std::thread::id main_thread_id, bool* force_colour_scheme,
                             bool* use_dark_mode)
{
    while (*done == false)
    {
        if (*force_colour_scheme == false)
        {
            DWORD darkModeselected = 0;
            DWORD valueSize = sizeof(darkModeselected);
            LSTATUS status = RegGetValue(HKEY_CURRENT_USER,
                                         L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
                                         L"AppsUseLightTheme",
                                         RRF_RT_REG_DWORD, // Expecting a DWORD value
                                         nullptr,
                                         &darkModeselected,
                                         &valueSize);

            if (status == ERROR_SUCCESS)
            {
                ImGui::SetStyleMode(nullptr, darkModeselected == false);
            }
        }
        else // Colour scheme has been force
        {
            ImGui::SetStyleMode(nullptr, *use_dark_mode);
        }

        // Different Thread, we can sleep
        // TODO: Use event instead
        if (std::this_thread::get_id() != main_thread_id)
        {
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }
}
