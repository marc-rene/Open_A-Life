#pragma once
#include <imgui.h>
#include "Open_ALife.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include <d3d11.h>



namespace ImGui
{
    void Core_Window(A_LIFE::ALIFE_SCENARIO* Core_ref);
    void Parent_Window(bool* p_open = NULL);
    void Test_Window(bool* p_open = NULL);
    void Scenario_Maker_Window(bool* p_open = NULL);
    void NavmeshVisualiser(bool* p_open, ID3D11Device* g_pd3dDevice, ID3D11DeviceContext* g_pd3dDeviceContext, HWND*);
}
