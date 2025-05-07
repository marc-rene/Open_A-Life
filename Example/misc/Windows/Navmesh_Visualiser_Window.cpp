/* DirectX 11 specific libs */
#include <DirectXMath.h>
#include <d3dcompiler.h>
/* - - - - - - - - - - - - -*/
#include "3D Utils/Camera.h"
#include "All_Windows.h"
#include "Styles/custom_styles.h"

// Forward declarations
void RenderScene(ID3D11DeviceContext* context, Camera* p_local_camera);
void InitViewportResources(ID3D11Device*, ImVec2*);


// ---------------------------------------------------------------
// TODO: CLEAN UP THIS DIRECT MESS
// ---------------------------------------------------------------
static ID3D11Texture2D* g_viewportTexture = nullptr;
static ID3D11RenderTargetView* g_viewportRTV = nullptr;
static ID3D11ShaderResourceView* g_viewportSRV = nullptr;
static D3D11_VIEWPORT g_viewportDesc = {};
static bool g_initialised = false;


// Global for cube

ID3D11Buffer* g_pConstantBuffer = nullptr;
ID3D11VertexShader* g_pVertexShader = nullptr;
ID3D11PixelShader* g_pPixelShader = nullptr;
ID3D11InputLayout* g_pInputLayout = nullptr;


// DEBUG: DELETE LATER
ID3D11Buffer* g_pVertexBuffer = nullptr;
ID3D11Buffer* g_pIndexBuffer = nullptr;
static uInt g_dungeonIndexCount = 0;
static bool g_dungeonModelLoaded = false;
static bool g_showTestDungeon = false;
//====================


// Constant buffer struct
struct ConstantBuffer
{
    Matrix world;
    Matrix view;
    Matrix projection;
};

// Vertex format
struct Vertex
{
    Vector3 pos;
    Vector3 colour;
};

void LoadTestDungeonModel(ID3D11Device* device, A_LIFE::Level* levelmesh)
{
    levelmesh->SetStaticMeshData(std::filesystem::current_path() / "test dungeon.obj");

    const std::vector<float> vtx_buffer = levelmesh->LevelMeshData.vertices;
    const std::vector<int> idx_buffer = levelmesh->LevelMeshData.indices;
    
    std::vector<Vector3> vertex_buf_formatted = {};
    for (size_t i = 0; i + 2 < vtx_buffer.size(); i += 3)
        vertex_buf_formatted.push_back({ vtx_buffer[i], vtx_buffer[i + 1], vtx_buffer[i + 2] });

    std::vector<Vertex> vertices = {};
    for (Vector3 var : vertex_buf_formatted)
        vertices.push_back({ var, var });
    
    // Vertex buffer
    D3D11_BUFFER_DESC bd = { vertices.size()};
    D3D11_SUBRESOURCE_DATA initData = { vertices.data() };

    // Index buffer
    bd = { static_cast<UINT>(idx_buffer.size()) };
    initData = { idx_buffer.data() };
    device->CreateBuffer(&bd, &initData, &g_pIndexBuffer);

    // Constant buffer
    bd = { sizeof(ConstantBuffer) };
    bd.CPUAccessFlags = 0;
    bd.Usage = D3D11_USAGE_DEFAULT;
    device->CreateBuffer(&bd, nullptr, &g_pConstantBuffer);

    // Simple shader (compiled in-place)
    ID3DBlob* vsBlob = nullptr;
    ID3DBlob* psBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;

    const char* vsSrc =
        "cbuffer ConstantBuffer : register(b0) { matrix world; matrix view; matrix proj; };"
        "struct VS_IN { float3 pos : POSITION; float3 col : COLOR; };"
        "struct VS_OUT { float4 pos : SV_POSITION; float3 col : COLOR; };"
        "VS_OUT main(VS_IN input) {"
        "    VS_OUT output;"
        "    float4 worldPos = mul(float4(input.pos, 1.0), world);"
        "    output.pos = mul(worldPos, view);"
        "    output.pos = mul(output.pos, proj);"
        "    output.col = input.col;"
        "    return output;"
        "}";

    const char* psSrc =
        "struct VS_OUT { float4 pos : SV_POSITION; float3 col : COLOR; };"
        "float4 main(VS_OUT input) : SV_Target { return float4(input.col, 1.0); }";

    D3DCompile(vsSrc, strlen(vsSrc), nullptr, nullptr, nullptr, "main", "vs_5_0", 0, 0, &vsBlob, &errorBlob);
    D3DCompile(psSrc, strlen(psSrc), nullptr, nullptr, nullptr, "main", "ps_5_0", 0, 0, &psBlob, &errorBlob);
    
    device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &g_pVertexShader);
    device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &g_pPixelShader);

    // Input layout
    D3D11_INPUT_ELEMENT_DESC layout[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, pos), D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, colour), D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    device->CreateInputLayout(layout, 2, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &g_pInputLayout);

    vsBlob->Release();
    psBlob->Release();
    // ------------------------

    /*
    struct SimpleVertex { DirectX::XMFLOAT3 position; };
    std::vector<SimpleVertex> gpuVerts;
    for (size_t i = 0; i + 2 < vtx_buffer.size(); i += 3)
        gpuVerts.push_back({ {vtx_buffer[i], vtx_buffer[i + 1], vtx_buffer[i + 2]} });

    // Create vertex buffer
    D3D11_BUFFER_DESC vbDesc{};
    vbDesc.Usage = D3D11_USAGE_DEFAULT;
    vbDesc.ByteWidth = sizeof(SimpleVertex) * gpuVerts.size();
    vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vbData{ gpuVerts.data() };
    if (FAILED(device->CreateBuffer(&vbDesc, &vbData, &g_pVertexBuffer))) {
        ERRORc("Failed to create vertex buffer for dungeon model");
        return;
    }

    // Create index buffer
    D3D11_BUFFER_DESC ibDesc{};
    ibDesc.Usage = D3D11_USAGE_DEFAULT;
    ibDesc.ByteWidth = sizeof(uInt) * idx_buffer.size();
    ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

   
    D3D11_SUBRESOURCE_DATA ibData{ idx_buffer.data() };
    if(device->CreateBuffer(&ibDesc, &ibData, &g_pIndexBuffer)) 
    {
        ERRORc("Failed to create index buffer for dungeon model");
    }

    g_dungeonIndexCount = static_cast<uInt>(idx_buffer.size());
    g_dungeonModelLoaded = true;
    SUCCESSc("Dungeon model loaded: {} verts, {} indices", gpuVerts.size(), g_dungeonIndexCount);
    */
}

void InitCube(ID3D11Device* device)
{
    // Define cube vertices
    Vertex vertices[] =
    {
        {{-1, -1, -1}, {1, 0, 0}}, {{-1, +1, -1}, {0, 1, 0}}, {{+1, +1, -1}, {0, 0, 1}}, {{+1, -1, -1}, {1, 1, 0}},
        // back
        {{-1, -1, +1}, {1, 0, 1}}, {{-1, +1, +1}, {0, 1, 1}}, {{+1, +1, +1}, {1, 1, 1}}, {{+1, -1, +1}, {0, 0, 0}},
        // front
    };

    // Indices
    uint16_t indices[] =
    {
        0, 1, 2, 0, 2, 3, // back
        4, 6, 5, 4, 7, 6, // front
        4, 5, 1, 4, 1, 0, // left
        3, 2, 6, 3, 6, 7, // right
        1, 5, 6, 1, 6, 2, // top
        4, 0, 3, 4, 3, 7 // bottom
    };

    // Vertex buffer
    D3D11_BUFFER_DESC bd = {
        sizeof(vertices),
    };
    D3D11_SUBRESOURCE_DATA initData = { vertices };
    device->CreateBuffer(&bd, &initData, &g_pVertexBuffer);

    // Index buffer
    bd = { sizeof(indices) };
    initData = { indices };
    device->CreateBuffer(&bd, &initData, &g_pIndexBuffer);

    // Constant buffer
    bd = { sizeof(ConstantBuffer) };
    bd.CPUAccessFlags = 0;
    bd.Usage = D3D11_USAGE_DEFAULT;
    device->CreateBuffer(&bd, nullptr, &g_pConstantBuffer);

    // Simple shader (compiled in-place)
    ID3DBlob* vsBlob = nullptr;
    ID3DBlob* psBlob = nullptr;
    ID3DBlob* errorBlob = nullptr;

    const char* vsSrc =
        "cbuffer ConstantBuffer : register(b0) { matrix world; matrix view; matrix proj; };"
        "struct VS_IN { float3 pos : POSITION; float3 col : COLOR; };"
        "struct VS_OUT { float4 pos : SV_POSITION; float3 col : COLOR; };"
        "VS_OUT main(VS_IN input) {"
        "    VS_OUT output;"
        "    float4 worldPos = mul(float4(input.pos, 1.0), world);"
        "    output.pos = mul(worldPos, view);"
        "    output.pos = mul(output.pos, proj);"
        "    output.col = input.col;"
        "    return output;"
        "}";

    const char* psSrc =
        "struct VS_OUT { float4 pos : SV_POSITION; float3 col : COLOR; };"
        "float4 main(VS_OUT input) : SV_Target { return float4(input.col, 1.0); }";

    D3DCompile(vsSrc, strlen(vsSrc), nullptr, nullptr, nullptr, "main", "vs_5_0", 0, 0, &vsBlob, &errorBlob);
    D3DCompile(psSrc, strlen(psSrc), nullptr, nullptr, nullptr, "main", "ps_5_0", 0, 0, &psBlob, &errorBlob);

    device->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &g_pVertexShader);
    device->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &g_pPixelShader);

    // Input layout
    D3D11_INPUT_ELEMENT_DESC layout[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, pos), D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(Vertex, colour), D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    device->CreateInputLayout(layout, 2, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &g_pInputLayout);

    vsBlob->Release();
    psBlob->Release();
}


void ImGui::NavmeshVisualiser(bool* p_open, ID3D11Device* g_pd3dDevice, ID3D11DeviceContext* g_pd3dDeviceContext,
                              A_LIFE::ALIFE_SCENARIO* ALIFEScenario)
{
    static Camera local_camara;
    static ImDrawListSplitter splitter;
    float clearColour[4] = {Accent_darken.x, Accent_darken.y, Accent_darken.z, 1.0f};
    static bool initialised = false;
    static ImVec2 viewportSize;
    static ImVec2 prev_viewport_size = viewportSize;

    g_pd3dDeviceContext->OMSetRenderTargets(1, &g_viewportRTV, nullptr);
    g_pd3dDeviceContext->RSSetViewports(1, &g_viewportDesc);
    g_pd3dDeviceContext->ClearRenderTargetView(g_viewportRTV, clearColour);


    PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    Begin("Navmesh Visualiser");
    PopStyleVar();

    // TODO: This will not show due to INTEL ARC driver issues. Must make this MAIN MENU for now.
    static constexpr bool using_INTEL_GPU = true;
    if (using_INTEL_GPU ? BeginMainMenuBar() : BeginMenuBar())
    {
        if (BeginMenu("View"))
        {
            if (MenuItem("Reset View"))
                local_camara.Reset_Position();
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

    PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    viewportSize = GetContentRegionAvail();
    if (!initialised)
    {
        InitViewportResources(g_pd3dDevice, &viewportSize);
        prev_viewport_size = viewportSize;
    }
    else if (viewportSize.x != prev_viewport_size.x || viewportSize.y != prev_viewport_size.y)
    {
        if (!IsMouseDown(ImGuiMouseButton_Left))
        {
            prev_viewport_size = viewportSize;
            InitViewportResources(g_pd3dDevice, &viewportSize);
            INFO("Navmesh Vis", "Viewport resized to: {} x {}", prev_viewport_size.x, prev_viewport_size.y);
        }
    }

    // Thanks https://github.com/ocornut/imgui/issues/5312
    splitter.Split(GetWindowDrawList(), 2);


    // Render text first, however, put it to the top layer so it is rendered on top of viewport image.
    splitter.SetCurrentChannel(GetWindowDrawList(), 1);
    Text("%s", local_camara.to_string().c_str());

    ImGui::SetCursorPos(GetWindowContentRegionMin());

    splitter.SetCurrentChannel(GetWindowDrawList(), 0);

    Image((ImTextureID)g_viewportSRV, viewportSize);
    PopStyleVar();

    splitter.Merge(GetWindowDrawList());

    if (!initialised)
    {
        A_LIFE::Level* DebugLevel = static_cast<A_LIFE::Level*>(A_LIFE::ALIFE_CoreObject::ObjectRegistry[*(ALIFEScenario->allLevels[0])]); 
        if (DebugLevel->LevelMeshData.indices.empty())
        {
            //DebugLevel->SetStaticMeshData(std::filesystem::current_path() / "test dungeon.obj");
        }
        SUCCESS("Navmesh Vis", "WE ABOUT TO LOAD UP A {}", *(ALIFEScenario->allLevels[0]));
        LoadTestDungeonModel(g_pd3dDevice, DebugLevel);
        //InitCube(g_pd3dDevice);
        initialised = true;
    }

    RenderScene(g_pd3dDeviceContext, &local_camara);
    End();
}


void InitViewportResources(ID3D11Device* device, ImVec2* size)
{
    if (g_viewportTexture)
    {
        g_viewportTexture->Release();
        g_viewportRTV->Release();
        g_viewportSRV->Release();
    }

    D3D11_TEXTURE2D_DESC texDesc = {};
    texDesc.Width = static_cast<UINT>(size->x);
    texDesc.Height = static_cast<UINT>(size->y);
    texDesc.MipLevels = 1;
    texDesc.ArraySize = 1;
    texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    texDesc.SampleDesc.Count = 1;
    texDesc.Usage = D3D11_USAGE_DEFAULT;
    texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;

    device->CreateTexture2D(&texDesc, nullptr, &g_viewportTexture);
    device->CreateRenderTargetView(g_viewportTexture, nullptr, &g_viewportRTV);
    device->CreateShaderResourceView(g_viewportTexture, nullptr, &g_viewportSRV);

    g_viewportDesc.TopLeftX = 0;
    g_viewportDesc.TopLeftY = 0;
    g_viewportDesc.Width = size->x;
    g_viewportDesc.Height = size->y;
    g_viewportDesc.MinDepth = 0.0f;
    g_viewportDesc.MaxDepth = 1.0f;

    INFO("Navmesh Vis", "Viewport inited to: {} x {}", size->x, size->y);
}


void RenderScene(ID3D11DeviceContext* context, Camera* p_local_camera)
{
    static float aspect;
    static ImGuiIO& ImGui_IO_ref = ImGui::GetIO();

    aspect = ImGui::GetWindowSize().x / ImGui::GetWindowSize().y;
    p_local_camera->onUpdate(&ImGui_IO_ref);

    Matrix view = p_local_camera->GetViewMatrix();
    Matrix world = MatrixIdentity();
    Matrix proj = MatrixPerspective(45.0f * DEG2RAD, aspect, 0.1f, 100.0f);

    ConstantBuffer cb;
    memcpy(&cb.world, &world, sizeof(Matrix));
    memcpy(&cb.view, &view, sizeof(Matrix));
    memcpy(&cb.projection, &proj, sizeof(Matrix));
    context->UpdateSubresource(g_pConstantBuffer, 0, nullptr, &cb, 0, 0);

    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    context->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);
    context->IASetIndexBuffer(g_pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->IASetInputLayout(g_pInputLayout);
    context->VSSetShader(g_pVertexShader, nullptr, 0);
    context->VSSetConstantBuffers(0, 1, &g_pConstantBuffer);
    context->PSSetShader(g_pPixelShader, nullptr, 0);
    
    context->DrawIndexed(262144, 0, 0);

    /*if (g_dungeonModelLoaded) {
        UINT stride = sizeof(DirectX::XMFLOAT3);
        UINT offset = 0;

        context->IASetVertexBuffers(0, 1, &g_dungeonVertexBuffer, &stride, &offset);
        context->IASetIndexBuffer(g_dungeonIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
        context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        context->IASetInputLayout(g_pInputLayout); // reuse cube input layout
        context->VSSetShader(g_pVertexShader, nullptr, 0);
        context->VSSetConstantBuffers(0, 1, &g_pConstantBuffer);
        context->PSSetShader(g_pPixelShader, nullptr, 0);

        context->DrawIndexed(g_dungeonIndexCount, 0, 0);
    }*/
}

