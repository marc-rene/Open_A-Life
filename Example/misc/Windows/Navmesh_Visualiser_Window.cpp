/* DirectX 11 specific libs */
#include <DirectXMath.h>
#include <d3dcompiler.h>
/* - - - - - - - - - - - - -*/
#include "raymath.h"
#include "3D Utils/Camera.h"
#include "All_Windows.h"
#include "Styles/custom_styles.h"

// Forward declarations
void RenderScene(ID3D11DeviceContext* context);
void InitViewportResources(ID3D11Device*);



// ---------------------------------------------------------------
// TODO: CLEAN UP THIS DIRECT MESS
// ---------------------------------------------------------------
static ID3D11Texture2D* g_viewportTexture = nullptr;
static ID3D11RenderTargetView* g_viewportRTV = nullptr;
static ID3D11ShaderResourceView* g_viewportSRV = nullptr;
static D3D11_VIEWPORT g_viewportDesc = {};
static bool g_initialised = false;


// Global for cube
ID3D11Buffer* g_pVertexBuffer = nullptr;
ID3D11Buffer* g_pIndexBuffer = nullptr;
ID3D11Buffer* g_pConstantBuffer = nullptr;
ID3D11VertexShader* g_pVertexShader = nullptr;
ID3D11PixelShader* g_pPixelShader = nullptr;
ID3D11InputLayout* g_pInputLayout = nullptr;


struct CameraController
{
	Vector3 position;
	Vector3 forward;
	Vector3 right;
	Vector3 up;

	float yaw = 0.0f;
	float pitch = 0.0f;
	float baseMoveSpeed = 3.0f;
	float turnSpeed = 1.5f;

	CameraController()
	{
		position = { 0.0f, 0.0f, 2.0f }; // Start 2 units above ground
		yaw = 0.0f;
		pitch = 0.0f;
		forward = { 1.0f, 0.0f, 0.0f }; // Facing +X
		right = { 0.0f, 1.0f, 0.0f }; // +Y is right
		up = { 0.0f, 0.0f, 1.0f }; // +Z is up
	}

	std::string to_string()
	{
		std::stringstream ss;
		ss << std::format("\tPosition = X: {:.2f} Y: {:.2f} Z: {:.2f}\n", position.x, position.y, position.z);
		ss << std::format("\tForward = X: {:.2f} Y: {:.2f} Z: {:.2f}\n", forward.x, forward.y, forward.z);
		ss << std::format("\tRight = X: {:.2f} Y: {:.2f} Z: {:.2f}\n", right.x, right.y, right.z);
		ss << std::format("\tUp = X: {:.2f} Y: {:.2f} Z: {:.2f}\n", up.x, up.y, up.z);
		return ss.str();
	}

	void Update(ImGuiIO* IO_ref)
	{
		static float speed_scaled;
		static float mouse_sensitivity = 0.0015f;
		static float current_move_speed;
		static bool captured = false;



		if (ImGui::IsKeyDown(ImGuiKey_LeftShift) || ImGui::IsKeyDown(ImGuiKey_RightShift))
			current_move_speed = baseMoveSpeed * 6;
		else
			current_move_speed = baseMoveSpeed;

		speed_scaled = current_move_speed * IO_ref->DeltaTime;

		// Movement keys
		if (ImGui::IsKeyDown(ImGuiKey_W))
			position = Vector3Add(position, Vector3Scale(forward, speed_scaled));

		if
			(ImGui::IsKeyDown(ImGuiKey_S))
			position = Vector3Subtract
			(position
				,
				Vector3Scale(forward, speed_scaled)
			);

		if
			(ImGui::IsKeyDown(ImGuiKey_A))
			position = Vector3Add
			(position
				,
				Vector3Scale(right, speed_scaled)
			);

		if
			(ImGui::IsKeyDown(ImGuiKey_D))
			position = Vector3Subtract
			(position
				,
				Vector3Scale(right, speed_scaled)
			);

		if
			(ImGui::IsKeyDown(ImGuiKey_E))
			position = Vector3Add
			(position
				,
				Vector3Scale(up, speed_scaled)
			);

		if
			(ImGui::IsKeyDown(ImGuiKey_Q))
			position = Vector3Subtract
			(position
				,
				Vector3Scale(up, speed_scaled)
			);

		// Mouse control
		bool process_mouse = captured || ((ImGui::IsMouseDown(ImGuiMouseButton_Right) ||
			ImGui::IsMouseDown(ImGuiMouseButton_Left)) && ImGui::IsWindowHovered());

		if(process_mouse)
			{
			if (!captured)
			{
				INFOc("GOT YA");
				captured = true;
			}


			yaw -= IO_ref->MouseDelta.x * mouse_sensitivity;
			pitch -= IO_ref->MouseDelta.y * mouse_sensitivity;
			//INFOc("Mouse Delat X: {} Y: {}", ImGui::MouseRawDeltaX, ImGui::MouseRawDeltaY);
			//pitch = Clamp(pitch, -PI_DIV_2 + 0.001f, PI_DIV_2 - 0.001f);
		}

		if
			(
				!
				ImGui::IsMouseDown(ImGuiMouseButton_Right) &&
				!
				ImGui::IsMouseDown(ImGuiMouseButton_Left)
				)
		{
			if (captured)
			{
				INFOc("lost ya");
				captured = false;
			}
		}

		// Recompute basis vectors
		forward =
		{
			cosf(pitch) * cosf(yaw),
			cosf(pitch) * sinf(yaw),
			sinf(pitch)
		};

		right = Vector3Normalize
		(Vector3CrossProduct({ 0.0f, 0.0f, 1.0f }
			,
			forward
		)
		);
		up = Vector3Normalize
		(Vector3CrossProduct(forward, right));

		//ImGui::MouseRawDeltaX = 0;
		//ImGui::MouseRawDeltaY = 0;
	}

	Matrix GetViewMatrix() const
	{
		Vector3 target = Vector3Add(position, forward);
		return MatrixLookAt(position, target, up);
	}
};

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
	HWND* hwnd)
{
	InitViewportResources(g_pd3dDevice);

	g_pd3dDeviceContext->OMSetRenderTargets(1, &g_viewportRTV, nullptr);
	g_pd3dDeviceContext->RSSetViewports(1, &g_viewportDesc);

	float clearColour[4] = { Accent_darken.x, Accent_darken.y, Accent_darken.z, 1.0f };
	g_pd3dDeviceContext->ClearRenderTargetView(g_viewportRTV, clearColour);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
	ImGui::Begin("Navmesh Visualiser");

	ImVec2 viewportSize = ImGui::GetContentRegionAvail();
	ImGui::Image((ImTextureID)g_viewportSRV, viewportSize);
	static bool initialised = false;
	if (!initialised)
	{
		InitCube(g_pd3dDevice);
		initialised = true;
	}

	// Render target must already be bound before this call
	RenderScene(g_pd3dDeviceContext);
	ImGui::End();
	ImGui::PopStyleVar();
	//CenterMouse(*hwnd);
}


void InitViewportResources(ID3D11Device* device)
{
	if (g_initialised) return;

	D3D11_TEXTURE2D_DESC texDesc = {};
	texDesc.Width = static_cast<UINT>(ImGui::GetContentRegionAvail().x);
	texDesc.Height = static_cast<UINT>(ImGui::GetContentRegionAvail().y);
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
	g_viewportDesc.Width = static_cast<float>(texDesc.Width);
	g_viewportDesc.Height = static_cast<float>(texDesc.Height);
	g_viewportDesc.MinDepth = 0.0f;
	g_viewportDesc.MaxDepth = 1.0f;

	g_initialised = true;
}


void RenderScene(ID3D11DeviceContext* context)
{
	static Camera cam{};
	static float aspect;
	static float angle = 0.0f;
	static ImGuiIO& ImGui_IO_ref = ImGui::GetIO();


	aspect = ImGui::GetWindowSize().x / ImGui::GetWindowSize().y;
	angle += 0.01f;

	cam.onUpdate(&ImGui_IO_ref);


	ImGui::Text("%s", cam.to_string().c_str());
	ImGui::Text("Mouse Delta X: %.3f  Y: %.3f", ImGui_IO_ref.MouseDelta.x, ImGui_IO_ref.MouseDelta.y);

	Matrix view = cam.GetViewMatrix();
	Matrix world = MatrixRotateZ(angle);
	Matrix proj = MatrixPerspective(45.0f * DEG2RAD, aspect, 0.1f, 100.0f);


	// Now set these to your constant buffer
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

	context->DrawIndexed(36, 0, 0);
}
