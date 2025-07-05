#include "Camera.h"

Camera::Camera()
{
    yaw = pitch = 0.0f;
    activeControlScheme = None;

    // We're using UDK Co-ordinate axis 
    forwardVector = {1.0f, 0.0f, 0.0f}; // +X is front
    rightVector = {0.0f, 1.0f, 0.0f}; // +Y is right
    upVector = {0.0f, 0.0f, 1.0f}; // +Z is up

    Reset_Position();

    Mouse_Captured = false;
}

Camera::Camera(Vector3 p_position, Vector3 p_target)
{
    worldPosition = p_position;
    activeControlScheme = None;

    Vector3 temp_direction = Vector3Normalize(Vector3Subtract(p_target, p_position));
    pitch = asinf(temp_direction.z);
    yaw = atan2f(temp_direction.y, temp_direction.x);


    recomputeVectors();

    Mouse_Captured = false;
}

void Camera::Reset_Position()
{
    worldPosition = {4.0f, 24.0f, 13.0f};
    yaw = 0;
    pitch = 0;
}


std::string Camera::to_string()
{
    std::stringstream ss;
    ss << std::format(
        "\n\t\t###\tMouse wont be captured in window. Mouse must stay in window in order to move camera\n");
    ss << std::format("\n- - - Camera Controls (Unreal Engine 5 style)  - - - - - - - - - - - - - - - - - -\n");

    ss << std::format("\tMovement = W A S D\n");
    ss << std::format("\tUp/Down = E Q\n\n");

    ss << std::format("\t -- Mouse Controls --\n");
    ss << std::format("\tFree-view = hold RIGHT mouse button \n");
    ss << std::format("\tTank Controls = hold LEFT mouse button\n");
    ss << std::format("\tWall-climb = hold Left AND Right mouse button\n");

    ss << std::format("\tBase Move Speed = {}\n", baseMoveSpeed);
    ss << std::format("\tAcceleration multiplier = {}\n", accelerateMult);
    ss << std::format("\tInvert Horizontal Look? = {}\n", invertHorizontal);
    ss << std::format("\tInvert Vertical Look? = {}\n", invertVertical);
    ss << std::format("\tMouse Sensitivity = Horizontal: {} Vertical: {}\n", mouseSensitivity.x, mouseSensitivity.y);


    switch (activeControlScheme)
    {
    case (flight_controls):
        ss << "\tCurrent Control Scheme: flight controls\n";
        break;
    case (tank_controls):
        ss << "\tCurrent Control Scheme: tank controls\n";
        break;
    case (vertical_climber):
        ss << "\tCurrent Control Scheme: vertical climber\n";
        break;
    case (pivot_swinger):
        ss << "\tCurrent Control Scheme: pivot swinger\n";
        break;
    default:
        break;
    }


    ss << std::format("\tCapturing Mouse input? = {}", Mouse_Captured ? "Yes\n" : "No\n");
    ss << std::format(" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");

    ss << std::format("\n - - - Camera Properties   - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
    ss << std::format("\tPosition = X: {:.2f} Y: {:.2f} Z: {:.2f}\n", worldPosition.x, worldPosition.y,
                      worldPosition.z);
    ss << std::format("\tForward = X: {:.2f} Y: {:.2f} Z: {:.2f}\n", forwardVector.x, forwardVector.y, forwardVector.z);
    ss << std::format("\tRight = X: {:.2f} Y: {:.2f} Z: {:.2f}\n", rightVector.x, rightVector.y, rightVector.z);
    ss << std::format("\tUp = X: {:.2f} Y: {:.2f} Z: {:.2f}\n", upVector.x, upVector.y, upVector.z);
    ss << std::format("\tYaw (Z-axis) = {}\n", yaw);
    ss << std::format("\tPitch (Y-axis)= {}\n", pitch);
    ss << std::format(" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -");

    return ss.str();
}

void Camera::recomputeVectors()
{
    // redo main camera vectors
    forwardVector = {
        cosf(yaw) * cosf(pitch),
        sinf(yaw) * cosf(pitch),
        sinf(pitch)
    };

    //upVector = Vector3Normalize(Vector3CrossProduct(forwardVector, rightVector));
    //rightVector = Vector3Normalize(Vector3CrossProduct({0.0f, 0.0f, 1.0f}, forwardVector));
    
    rightVector = Vector3Normalize(Vector3CrossProduct(Vector3(0,0,1.0f), forwardVector));
    upVector = Vector3Normalize(Vector3CrossProduct(forwardVector, rightVector));
}

void Camera::onUpdate(ImGuiIO* IO_ref)
{
    if (ImGui::IsItemHovered())
    {
        ProcessMouse(IO_ref);
        ProcessKeyboard(IO_ref);
    }

    recomputeVectors();
}


bool Camera::ProcessMouse(ImGuiIO* IO_ref)
{
    // Scroll in/out
    if (IO_ref->MouseWheel > 0 || IO_ref->MouseWheel < 0)
    {
        // INFO("Mouse Debug", "Scroll is {}", IO_ref->MouseWheel);
        worldPosition = Vector3Add(
            worldPosition, Vector3Multiply(forwardVector,
                                           {IO_ref->MouseWheel, IO_ref->MouseWheel, IO_ref->MouseWheel}));
    }

    // Release
    if (!(ImGui::IsMouseDown(ImGuiMouseButton_Left) || ImGui::IsMouseDown(ImGuiMouseButton_Right) ||
        ImGui::IsMouseDown(ImGuiMouseButton_Middle)) && Mouse_Captured)
    {
        Mouse_Captured = false;
        activeControlScheme = None;
        // INFO("Mouse Debug", "Mouse lost");
        return false;
    }

    // GOT YA
    if ((ImGui::IsMouseDown(ImGuiMouseButton_Left) || ImGui::IsMouseDown(ImGuiMouseButton_Right) ||
        ImGui::IsMouseDown(ImGuiMouseButton_Middle)) && !Mouse_Captured)
    {
        Mouse_Captured = true;
        // INFO("Mouse Debug", "Mouse CAPTURED");
    }

    // Only right click
    if (!ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsMouseDown(ImGuiMouseButton_Right) && Mouse_Captured)
    {
        activeControlScheme = flight_controls;
        Look_Right(IO_ref->MouseDelta.x * mouseSensitivity.x);
        Look_Up(IO_ref->MouseDelta.y * mouseSensitivity.y);
        // INFO("Mouse Debug", "Right click");
        return true;
    }

    // Only left click
    if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && !ImGui::IsMouseDown(ImGuiMouseButton_Right) && Mouse_Captured)
    {
        activeControlScheme = tank_controls;
        Look_Right(IO_ref->MouseDelta.x * mouseSensitivity.x);
        Move_Backward(IO_ref->MouseDelta.y * mouseSensitivity.y * baseMoveSpeed, true);
        // INFO("Mouse Debug", "Left click");
        return true;
    }

    // BOTH
    if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsMouseDown(ImGuiMouseButton_Right) && Mouse_Captured)
    {
        activeControlScheme = vertical_climber;
        Move_Down(IO_ref->MouseDelta.y * mouseSensitivity.y * baseMoveSpeed, true);
        Move_Right(IO_ref->MouseDelta.x * mouseSensitivity.x * baseMoveSpeed);
        // INFO("Mouse Debug", "Both down");
        return true;
    }

    // TODO: This is launches us
    /*
    else if (ImGui::IsMouseDown(ImGuiMouseButton_Middle) && Mouse_Captured)
    {
        activeControlScheme = EcontrolMode::pivot_swinger;

        Vector3 new_pivot = Vector3Add(worldPosition, Vector3Multiply(forwardVector, {500, 0, 0}));
        Pivot_Around(new_pivot, {
                         (IO_ref->MouseDelta.x * IO_ref->DeltaTime * mouseSensitivity.x),
                         (IO_ref->MouseDelta.y * IO_ref->DeltaTime * mouseSensitivity.y)
                     });
    }*/

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


    //TODO: change this into a single vector3 called "movement this frame" so that keyboard keys just inc/decrint it
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
        Move_Up(speed_scaled, true);

    if (ImGui::IsKeyDown(ImGuiKey_Q))
        Move_Down(speed_scaled, true);
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
                                       clamp_2D_movement ? 0 : upVector.x,
                                       clamp_2D_movement ? 0 : upVector.y,
                                       clamp_2D_movement ? 1 : upVector.z
                                   }, scale));
}

void Camera::Move_Down(float scale, bool clamp_2D_movement)
{
    worldPosition = Vector3Subtract(worldPosition, Vector3Scale(
                                        {
                                            clamp_2D_movement ? 0 : upVector.x,
                                            clamp_2D_movement ? 0 : upVector.y,
                                            clamp_2D_movement ? 1 : upVector.z
                                        }, scale));
}

// TODO: This launches the camera into the stratosphere 
void Camera::Pivot_Around(Vector3 pivot_around, Vector2 scale)
{
    // Update yaw and pitch
    yaw += scale.x;
    pitch += scale.y;

    // Clamp pitch so you don't flip upside down (optional, but recommended)
    constexpr float max_pitch = DEG2RAD * 89.9f;
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

    worldPosition = Vector3Add(offset, newOffset);
}

void Camera::Look_Up(float amount)
{
    pitch += (amount * (invertVertical ? 1.0f : -1.0f));
    pitch = Clamp(pitch, (-(PI / 2) + EPSILON), ((PI / 2) - EPSILON));
    recomputeVectors();
}

void Camera::Look_Right(float amount)
{
    yaw -= (amount * (invertHorizontal ? -1.0f : 1.0f));
    recomputeVectors();
}

Matrix Camera::GetViewMatrix() const
{
    Vector3 target = Vector3Add(worldPosition, forwardVector);
    return MatrixLookAt(worldPosition, target, {0,0,1});
}
