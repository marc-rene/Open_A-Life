#pragma once

#include <glad/glad.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include "Open_ALife.h"
#include "Styles/custom_styles.h"


namespace ImGui
{
    void Core_Window(A_LIFE::ALIFE_SCENARIO* Core_ref);
    void Parent_Window(bool* p_open = nullptr);
    void Test_Window(bool* p_open = nullptr);
    void Scenario_Maker_Window(bool* p_open = nullptr);
    void NavmeshVisualiser(bool* p_open, A_LIFE::ALIFE_SCENARIO*);
}

int CreateAppWindow(A_LIFE::ALIFE_SCENARIO*);
static GLFWwindow* window;