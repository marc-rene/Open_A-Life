#pragma once
#include "imgui.h"
#include "raymath.h"
#include "Windows/All_Windows.h"

class Camera
{
    enum EcontrolMode : uMint
    {
        None = 0, // Nothing
        flight_controls = 1, // Hold right click
        tank_controls = 2, // Hold left click
        vertical_climber = 3, // Hold both
        pivot_swinger = 4, // Swing around pivot
    };

public:
    Vector3 worldPosition;
    Vector3 forwardVector;
    Vector3 rightVector;
    Vector3 upVector;
    Vector2 mouseSensitivity = {0.0015f, 0.0015f,};
    EcontrolMode activeControlScheme;
    float yaw;
    float pitch;
    float baseMoveSpeed = 7.0f;
    float accelerateMult = 3.0f;
    bool invertHorizontal = false;
    bool invertVertical = false;
    bool Mouse_Captured;

    Camera();
    Camera(Vector3 p_position, Vector3 p_target);

    void Reset_Position();

    std::string to_string();

    void onUpdate(ImGuiIO* IO_ref);

    bool ProcessMouse(ImGuiIO* IO_ref);
    void ProcessKeyboard(ImGuiIO* IO_ref);

    // Movement - 2D (X & Y axis) / 3D
    void Move_Forward(float scale, bool clamp_2D_movement = false);
    void Move_Right(float scale);
    void Move_Backward(float scale, bool clamp_2D_movement = false);
    void Move_Left(float scale);
    void Move_Up(float scale, bool clamp_2D_movement = false);
    void Move_Down(float scale, bool clamp_2D_movement = false);
    void Pivot_Around(Vector3 pivot_around, Vector2 scale);

    // Rotation
    void Look_Up(float amount);
    void Look_Right(float amount);

    Matrix GetViewMatrix() const;
};
