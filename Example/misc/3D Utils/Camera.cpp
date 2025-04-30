#include "Camera.h"

Camera::Camera()
{
    worldPosition = {0};
    yaw = pitch = 0.0f;
    activeControlScheme = EcontrolMode::None;

    // We're using UDK Co-ordinate axis 
    forwardVector = {1.0f, 0.0f, 0.0f}; // +X is front
    rightVector = {0.0f, 1.0f, 0.0f}; // +Y is right
    upVector = {0.0f, 0.0f, 1.0f}; // +Z is up

    Mouse_Captured = false;
}

Camera::Camera(Vector3 p_position, Vector3 p_target)
{
    worldPosition = p_position;
    activeControlScheme = EcontrolMode::None;

    Vector3 temp_direction = Vector3Normalize(Vector3Subtract(p_target, p_position));
    pitch = asinf(temp_direction.z);
    yaw = atan2f(temp_direction.y, temp_direction.x);

    forwardVector = {cosf(yaw) * cosf(pitch), sinf(yaw) * cosf(pitch), sinf(pitch)};
    rightVector = {-sinf(yaw), cosf(yaw), 0.0f};
    upVector = Vector3CrossProduct(rightVector, forwardVector);

    Mouse_Captured = false;
}


std::string Camera::to_string()
{
    std::stringstream ss;
    ss << std::format("\tPosition = X: {:.2f} Y: {:.2f} Z: {:.2f}\n", worldPosition.x, worldPosition.y,
                      worldPosition.z);
    ss << std::format("\tForward = X: {:.2f} Y: {:.2f} Z: {:.2f}\n", forwardVector.x, forwardVector.y, forwardVector.z);
    ss << std::format("\tRight = X: {:.2f} Y: {:.2f} Z: {:.2f}\n", rightVector.x, rightVector.y, rightVector.z);
    ss << std::format("\tUp = X: {:.2f} Y: {:.2f} Z: {:.2f}\n", upVector.x, upVector.y, upVector.z);
    ss << std::format("\tYaw (Z-axis) = {}\n", yaw);
    ss << std::format("\tPitch (Y-axis)= {}\n", pitch);
    ss << std::format("\tBase Move Speed = {}\n", baseMoveSpeed);
    
    ss << std::format("\tInvert Horizontal Look? = {}\n", invertHorizontal);
    ss << std::format("\tInvert Vertical Look? = {}\n", invertVertical);
    return ss.str();
}

void Camera::onUpdate(ImGuiIO* IO_ref)
{
    ProcessMouse(IO_ref);
    ProcessKeyboard(IO_ref);

    // Recompute basis vectors
    forwardVector = {
        cosf(pitch) * cosf(yaw),
        cosf(pitch) * sinf(yaw),
        sinf(pitch)
    };

    rightVector = Vector3Normalize(Vector3CrossProduct({0.0f, 0.0f, 1.0f}, forwardVector));
    upVector = Vector3Normalize(Vector3CrossProduct(forwardVector, rightVector));
}


bool Camera::ProcessMouse(ImGuiIO* IO_ref)
{
    if (!(ImGui::IsMouseDown(ImGuiMouseButton_Left) || ImGui::IsMouseDown(ImGuiMouseButton_Right) ||
        ImGui::IsMouseDown(ImGuiMouseButton_Middle)) && Mouse_Captured)
    {
        Mouse_Captured = false;
        activeControlScheme = EcontrolMode::None;
        INFO("Mouse Debug", "Mouse lost");
        return false;
    }

    if ((ImGui::IsMouseDown(ImGuiMouseButton_Left) || ImGui::IsMouseDown(ImGuiMouseButton_Right) ||
        ImGui::IsMouseDown(ImGuiMouseButton_Middle)) && !Mouse_Captured)
    {
        Mouse_Captured = true;
        INFO("Mouse Debug", "Mouse CAPTURED");
    }

    // Only right click
    if (!ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsMouseDown(ImGuiMouseButton_Right) && Mouse_Captured)
    {
        activeControlScheme = EcontrolMode::flight_controls;
        Look_Right(IO_ref->MouseDelta.x * mouseSensitivity.x);
        Look_Up(IO_ref->MouseDelta.y * mouseSensitivity.y);
        INFO("Mouse Debug", "Right click");
    }
    // Only left click
    else if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && !ImGui::IsMouseDown(ImGuiMouseButton_Right) && Mouse_Captured)
    {
        activeControlScheme = EcontrolMode::tank_controls;
        Look_Right(IO_ref->MouseDelta.x * mouseSensitivity.x);
        Move_Forward(IO_ref->MouseDelta.y * IO_ref->DeltaTime * mouseSensitivity.y);
        INFO("Mouse Debug", "Left click");
    }
    // BOTH
    else if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsMouseDown(ImGuiMouseButton_Right) && Mouse_Captured)
    {
        activeControlScheme = EcontrolMode::vertical_climber;
        Move_Up(IO_ref->MouseDelta.y * IO_ref->DeltaTime * mouseSensitivity.y);
        Move_Right(IO_ref->MouseDelta.x * IO_ref->DeltaTime * mouseSensitivity.x);
        INFO("Mouse Debug", "Both down");
    }

    else if (ImGui::IsMouseDown(ImGuiMouseButton_Middle) && Mouse_Captured)
    {
        INFOc("PIVOT THAT BOOTY");
        activeControlScheme = EcontrolMode::pivot_swinger;

        // pivot around a new point that is 5 units in front of us
        Vector3 new_pivot = Vector3Add(worldPosition, Vector3Multiply(forwardVector, {5}));
        Pivot_Around(new_pivot, {
                         (IO_ref->MouseDelta.x * IO_ref->DeltaTime * mouseSensitivity.x),
                         (IO_ref->MouseDelta.y * IO_ref->DeltaTime * mouseSensitivity.y)
                     });
    }



    return false;
}

void Camera::ProcessKeyboard(ImGuiIO* IO_ref)
{
    static float speed_scaled;
    static float current_move_speed;

    if (ImGui::IsKeyDown(ImGuiKey_LeftShift) || ImGui::IsKeyDown(ImGuiKey_RightShift))
        current_move_speed = baseMoveSpeed * 6;
    else
        current_move_speed = baseMoveSpeed;

    speed_scaled = current_move_speed * IO_ref->DeltaTime;

    // Movement keys
    if (ImGui::IsKeyDown(ImGuiKey_W))
        Move_Forward(speed_scaled);

    if (ImGui::IsKeyDown(ImGuiKey_S))
        Move_Backward(speed_scaled);

    if (ImGui::IsKeyDown(ImGuiKey_A))
        Move_Left(speed_scaled);

    if (ImGui::IsKeyDown(ImGuiKey_D))
        Move_Right(speed_scaled);

    if (ImGui::IsKeyDown(ImGuiKey_E))
        Move_Up(speed_scaled);

    if (ImGui::IsKeyDown(ImGuiKey_Q))
        Move_Down(speed_scaled);
}

void Camera::Move_Forward(float scale, bool clamp_2D_movement)
{
    worldPosition =
        Vector3Add(worldPosition, Vector3Scale({
                                                   forwardVector.x,
                                                   forwardVector.y,
                                                   clamp_2D_movement ? 0 : forwardVector.z
                                               }, scale));
}


void Camera::Move_Right(float scale)
{
    worldPosition =
        Vector3Subtract(worldPosition, Vector3Scale({
                                                        rightVector.x,
                                                        rightVector.y,
                                                        rightVector.z
                                                    }, scale));
}

void Camera::Move_Backward(float scale, bool clamp_2D_movement)
{
    worldPosition =
        Vector3Subtract(worldPosition, Vector3Scale({
                                                        forwardVector.x,
                                                        forwardVector.y,
                                                        clamp_2D_movement ? 0 : forwardVector.z
                                                    }, scale));
}

void Camera::Move_Left(float scale)
{
    worldPosition =
        Vector3Add(worldPosition, Vector3Scale({
                                                   rightVector.x,
                                                   rightVector.y,
                                                   rightVector.z
                                               }, scale));
}

void Camera::Move_Up(float scale, bool clamp_2D_movement)
{
    worldPosition = Vector3Add(worldPosition, Vector3Scale(
                                   {
                                       upVector.x,
                                       upVector.y,
                                       clamp_2D_movement ? 1 : upVector.z
                                   }, scale));
}

void Camera::Move_Down(float scale, bool clamp_2D_movement)
{
    worldPosition = Vector3Subtract(worldPosition, Vector3Scale(
                               {
                                   upVector.x,
                                   upVector.y,
                                   clamp_2D_movement ? 1 : upVector.z
                               }, scale));
}

void Camera::Pivot_Around(Vector3 pivot_around, Vector2 scale)
{
    // Update yaw and pitch
    yaw += scale.x;
    pitch += scale.y;

    // Clamp pitch so you don't flip upside down (optional, but recommended)
    const float max_pitch = DEG2RAD * 89.0f; // ~89 degrees to avoid gimbal lock
    if (pitch > max_pitch) pitch = max_pitch;
    if (pitch < -max_pitch) pitch = -max_pitch;

    // Calculate distance to pivot
    Vector3 offset = Vector3Subtract(worldPosition, pivot_around);
    float distance = Vector3Length(offset);

    // Recalculate new camera position based on yaw and pitch
    Vector3 newOffset = {
        distance * cosf(yaw) * cosf(pitch),
        distance * sinf(yaw) * cosf(pitch),
        distance * sinf(pitch)
    };

    worldPosition = Vector3Add(pivot_around, newOffset);

    // Update basis vectors
    forwardVector = Vector3Normalize(Vector3Subtract(pivot_around, worldPosition));
    rightVector = {-sinf(yaw), cosf(yaw), 0.0f};
    upVector = Vector3CrossProduct(rightVector, forwardVector);
}

void Camera::Look_Up(float amount)
{
    pitch += (amount * (invertVertical ? 1.0f : -1.0f));
    pitch = Clamp(pitch, (-(PI / 2) + EPSILON), ((PI / 2) - EPSILON));
}

void Camera::Look_Right(float amount)
{
    yaw -= (amount * (invertHorizontal ? -1.0f : 1.0f));
}

Matrix Camera::GetViewMatrix() const
{
    Vector3 target = Vector3Add(worldPosition, forwardVector);
    return MatrixLookAt(worldPosition, target, upVector);
}
