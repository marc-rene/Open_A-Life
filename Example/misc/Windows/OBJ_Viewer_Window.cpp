#include "Windows/All_Windows.h"

#include "3D Utils/Camera.h"
#include "Styles/custom_styles.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "TinyOBJ/tiny_obj_loader.h"



#include <vector>
#include <string>
#include <cmath>

namespace {
    struct ObjMesh {
        std::vector<Vector3> vertices;
        std::vector<int>  indices;
    };

    static ObjMesh gMesh;

    bool LoadObjMesh(const char* path)
    {
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;

        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path))
            return false;

        gMesh.vertices.clear();
        gMesh.indices.clear();

        for (const auto& shape : shapes)
        {
            for (const auto& idx : shape.mesh.indices)
            {
                Vector3 v{};
                v.x = attrib.vertices[3 * idx.vertex_index + 0];
                v.y = attrib.vertices[3 * idx.vertex_index + 1];
                v.z = attrib.vertices[3 * idx.vertex_index + 2];
                gMesh.vertices.push_back(v);
                gMesh.indices.push_back((int)gMesh.indices.size());
            }
        }
        return true;
    }

    ImVec2 Project(const Vector3& vertex, const Camera& cam, float scale, ImVec2 center)
    {

        float cy = cosf(cam.yaw);
        float sy = sinf(cam.yaw);
        float cp = cosf(cam.pitch);
        float sp = sinf(cam.pitch);


        // Translate the vertex relative to the camera's world position
        Vector3 vtx(
        vertex.x - cam.worldPosition.x,
        vertex.y - cam.worldPosition.y,
        vertex.z - cam.worldPosition.z
        );

        float x1 = cy * vtx.x + sy * vtx.z;
        float z1 = -sy * vtx.x + cy * vtx.z;
        float y1 = cp * vtx.y - sp * z1;
        float z2 = sp * vtx.y + cp * z1;

    
        float f = 1.0f / (z2 * 0.3f + 3.0f);
        return ImVec2(center.x + x1 * scale * f, center.y - y1 * scale * f);
    }
}

void ImGui::OBJ_Viewer_Window(bool* p_open)
{
    static char obj_path[256] = "";
    static Camera local_camera;
    static ImDrawListSplitter splitter;
    static ImGuiIO* IO_ref = &ImGui::GetIO();
    static bool initialised = false;
    static ImVec2 prevViewportSize;
    static const char* Window_Title = "Navmesh Visualiser";

    ImGui::Begin(Window_Title, p_open);
    

    if (!initialised)
        prevViewportSize = ImGui::GetContentRegionAvail();
    
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

    local_camera.onUpdate(&ImGui::GetIO());

    // Render text first, however, put it to the top layer so it is rendered on top of viewport image.
    splitter.Split(GetWindowDrawList(), 2); // Thanks https://github.com/ocornut/imgui/issues/5312
    splitter.SetCurrentChannel(GetWindowDrawList(), 0);

    ImVec2 avail = ImGui::GetContentRegionAvail();
    ImVec2 origin = ImGui::GetCursorScreenPos();
    ImVec2 center = ImVec2(origin.x + avail.x * 0.5f, origin.y + avail.y * 0.5f);
    float scale = avail.y * 0.5f;
    ImDrawList* dl = ImGui::GetWindowDrawList();

    for (size_t i = 0; i + 2 < gMesh.indices.size(); i += 3)
    {
        const Vector3& v0 = gMesh.vertices[gMesh.indices[i + 0]];
        const Vector3& v1 = gMesh.vertices[gMesh.indices[i + 1]];
        const Vector3& v2 = gMesh.vertices[gMesh.indices[i + 2]];

        ImVec2 p0 = Project(v0, local_camera, scale, center);
        ImVec2 p1 = Project(v1, local_camera, scale, center);
        ImVec2 p2 = Project(v2, local_camera, scale, center);

        // Skip triangles behind the camera (offscreen pushed to -1000, -1000)
        if (p0.x < -500 || p1.x < -500 || p2.x < -500)
            continue;

        dl->AddLine(p0, p1, IM_COL32(255, 5, 5, 255));
        dl->AddLine(p1, p2, IM_COL32(5, 255, 5, 255));
        dl->AddLine(p2, p0, IM_COL32(5, 5, 255, 255));
    }
    //ImGui::Image(nullptr, prevViewportSize, ImVec2(0, 1), ImVec2(1, 0));
    ImGui::Dummy(avail);
    local_camera.onUpdate(IO_ref);

    splitter.SetCurrentChannel(GetWindowDrawList(), 1);
    ImGui::SetCursorPos(GetWindowContentRegionMin());
    ImGui::InputText("OBJ Path", obj_path, sizeof(obj_path));
    ImGui::SameLine();
    
    if (ImGui::Button("Load"))
    {
        std::filesystem::path tempmeshpath = A_LIFE::File_Wizard::OpenFilePath("Mesh Files\0*.obj\0", "obj", "What mesh will we load");
        if (!tempmeshpath.empty())
            LoadObjMesh(tempmeshpath.string().c_str());
        else
        {
            WARNc("The .OBJ file {} is not halal", tempmeshpath.string())
        }
    }
    
    
    Text("%s", local_camera.to_string().c_str());

    splitter.Merge(GetWindowDrawList());

    ImGui::End();
}