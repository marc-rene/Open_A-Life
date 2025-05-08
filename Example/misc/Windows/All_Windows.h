#pragma once
#include <imgui.h>
#include "Open_ALife.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#define GL_SILENCE_DEPRECATION
#include <GLFW/glfw3.h> // Will drag system OpenGL headers


namespace ImGui
{
    void Core_Window(A_LIFE::ALIFE_SCENARIO* Core_ref);
    void Parent_Window(bool* p_open = nullptr);
    void Test_Window(bool* p_open = nullptr);
    void Scenario_Maker_Window(bool* p_open = nullptr);
    //void NavmeshVisualiser(bool* p_open, ID3D11Device* g_pd3dDevice, ID3D11DeviceContext* g_pd3dDeviceContext, A_LIFE::ALIFE_SCENARIO*);
}
