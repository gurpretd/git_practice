#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <shellscalingapi.h>
#include <DXGI1_5.h>
#include <dxgidebug.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "Shcore.lib") // Need for SetProcessDpiAwareness(...) to avoid wacky windows scaling.

using namespace DirectX;

// If there is a fatal error:
// * Create a Message Window
// * Print to console
// * Print to debug window
void myFatalError(const char* err, const char* title)
{
    constexpr size_t buffsize = 1024;
    std::unique_ptr<char[]> err_buff = std::make_unique<char[]>(buffsize);

    MessageBoxA(0, err, title, MB_OK);
    sprintf_s(err_buff.get(), buffsize, "Error <%s>: %s", title, err);
    puts(err_buff.get());
    OutputDebugStringA(err_buff.get());
}

// For a log string:
// * Print to console
// * Print to debug window
void myLogString(const char* str)
{
    puts(str);
    OutputDebugStringA(str);
}

// For a log string: (This version is for Wide char, some strings from windows like GPU name use this type of string.)
// * Print to console
// * Print to debug window
void myLogStringW(const WCHAR* wstr)
{
    constexpr size_t buffsize = 1024;
    std::unique_ptr<char[]> astr = std::make_unique<char[]>(buffsize);

    sprintf_s(astr.get(), buffsize, "%ls", wstr);
    
    puts(astr.get());
    OutputDebugStringA(astr.get());
    OutputDebugStringA("\n");
}

void _myassert_macrofunc(int chk, const char* file, int line)
{
    if(!chk)
    {
        constexpr size_t buffsize = 1024;
        std::unique_ptr<char[]> err_buff = std::make_unique<char[]>(buffsize);

        sprintf_s(err_buff.get(), buffsize, "Assertion in Source File: <%s>, line <%d>", file, line);

        myFatalError(err_buff.get(), "Assertion");
        exit(1);
    }
}

#define MYASSERT(x) _myassert_macrofunc((x), __FILE__, __LINE__)

#define MY_SAFE_RELEASE(x) if(x) { x->Release(); x = nullptr; }

static bool _winResized = false;

// Windows procedure for GUI Window - this handles messages for our window
LRESULT CALLBACK MyWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    LRESULT res = 0;

    switch(msg)
    {
    case WM_KEYDOWN:
        if(wparam == VK_ESCAPE)
            DestroyWindow(hwnd); // user hit escape, we''re done.
        break;
    case WM_DESTROY: // something happened to end the program (like window close button)
        PostQuitMessage(0);
        break;
    case WM_SIZING:
    case WM_SIZE:
    case WM_EXITSIZEMOVE:
        _winResized = true;
        break;
    default:
        res = DefWindowProcW(hwnd, msg, wparam, lparam); // call default windows procedure - default handling of messages
    }

    return res;
}

// This is the main entry point, like any other program. We'll have both a "Dos box" (for printf) as well as a GUI window.
int main(void)
{
    // Avoid wacky window streching, which will make for an ugly triangles or shapes. (Ignore DPI adjustments)
    SetProcessDpiAwareness(PROCESS_DPI_AWARENESS::PROCESS_SYSTEM_DPI_AWARE);

    LONG width = 600;
    LONG height = 450;

    // Create the GUI Window - this section is the same as a "regular" windows GUI program.
    HWND hwnd;
    {
        WNDCLASSEXW winClass = {};
        winClass.cbSize = sizeof(WNDCLASSEXW);
        winClass.style = CS_HREDRAW | CS_VREDRAW;
        winClass.lpfnWndProc = &MyWndProc;
        winClass.hInstance = 0;
        winClass.hIcon = LoadIconW(0, IDI_APPLICATION);
        winClass.hCursor = LoadCursorW(0, IDC_ARROW);
        winClass.lpszClassName = L"WinClass";
        winClass.hIconSm = LoadIconW(0, IDI_APPLICATION);

        if(!RegisterClassExW(&winClass)) 
        {
            myFatalError("RegisterClassExW() failed", "Fatal Error");
            return GetLastError();
        }

        RECT initialRect = { 0, 0, width, height }; // Default Window size

        // Need this if you use: WS_EX_OVERLAPPEDWINDOW in CreateWindowExW()
        // AdjustWindowRectEx(&initialRect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);
        LONG initialWidth = initialRect.right - initialRect.left;
        LONG initialHeight = initialRect.bottom - initialRect.top;

        hwnd = CreateWindowExW(0, winClass.lpszClassName, L"My DX Test",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
            initialWidth, initialHeight, 0, 0, 0, 0);

        if(!hwnd) 
        {
            myFatalError("CreateWindowExW() failed", "Fatal Error");
            return GetLastError();
        }
    }

    // Create D3D11.1 Device and Context
    ID3D11Device1* dxDevice = nullptr;
    ID3D11DeviceContext1* dxDeviceContext = nullptr;
    {
        D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_1 };
        UINT creationFlags = 0; // D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

        ID3D11Device* baseDevice;
        ID3D11DeviceContext* baseDeviceContext;
        HRESULT hr = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, creationFlags,
            featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &baseDevice, 0, &baseDeviceContext);
        
        if(FAILED(hr)) 
        {
            myFatalError("D3D11CreateDevice() failed", "Fatal Error");
            return GetLastError();
        }

        // get "DX 11.1" (specific) dev and context
        hr = baseDevice->QueryInterface(__uuidof(ID3D11Device1), (void**)&dxDevice);
        MYASSERT(SUCCEEDED(hr));
        MY_SAFE_RELEASE(baseDevice);

        hr = baseDeviceContext->QueryInterface(__uuidof(ID3D11DeviceContext1), (void**)&dxDeviceContext);
        MYASSERT(SUCCEEDED(hr));
        MY_SAFE_RELEASE(baseDeviceContext);
    }

#ifdef _DEBUG
    // If debug build, setup the debug layer tell us about DX errors
    ID3D11Debug* d3dDebug = nullptr;
    dxDevice->QueryInterface(__uuidof(ID3D11Debug), (void**)&d3dDebug);
    if(d3dDebug)
    {
        ID3D11InfoQueue* d3dInfoQueue = nullptr;
        if(SUCCEEDED(d3dDebug->QueryInterface(__uuidof(ID3D11InfoQueue), (void**)&d3dInfoQueue)))
        {
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
            d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
            MY_SAFE_RELEASE(d3dInfoQueue);
        }
    }
#endif

    IDXGISwapChain1* dxSwapChain = nullptr;
    {
        // Get DXGI Factory (needed to create swap chain)
        IDXGIFactory4* dxgiFactory = nullptr;
        {
            IDXGIDevice1* dxgiDevice = nullptr;
            HRESULT hr = dxDevice->QueryInterface(__uuidof(IDXGIDevice3), (void**)&dxgiDevice);
            MYASSERT(SUCCEEDED(hr));

            IDXGIAdapter* dxgiAdapter = nullptr;
            hr = dxgiDevice->GetAdapter(&dxgiAdapter);
            MYASSERT(SUCCEEDED(hr));
            MY_SAFE_RELEASE(dxgiDevice);

            DXGI_ADAPTER_DESC adapterDesc;
            dxgiAdapter->GetDesc(&adapterDesc);

            myLogString("GFX Device: ");
            myLogStringW(adapterDesc.Description);

            hr = dxgiAdapter->GetParent(__uuidof(IDXGIFactory4), (void**)&dxgiFactory);
            MYASSERT(SUCCEEDED(hr));
            MY_SAFE_RELEASE(dxgiAdapter);
        }

        DXGI_SWAP_CHAIN_DESC1 scd = {};

        scd.SampleDesc.Count = 1;
        scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        scd.BufferCount = 2;
        scd.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
        
        // Future performance consideration:
        // * Look at the docs: https://docs.microsoft.com/en-us/windows/win32/direct3ddxgi/for-best-performance--use-dxgi-flip-model
        // * Also watch: https://www.youtube.com/watch?v=E3wTajGZOsA
        // scd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

        scd.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // When you change to flip model (per above) it becomes: DXGI_FORMAT_R8G8RBA8_UNORM; you'll also need to change gamma in the pixel shader
                                                                  
        // Create swap chain
        HRESULT hr = dxgiFactory->CreateSwapChainForHwnd(dxDevice, hwnd, &scd, 0, 0, &dxSwapChain);
        MYASSERT(SUCCEEDED(hr));

        dxgiFactory->MakeWindowAssociation(hwnd, DXGI_MWA_NO_ALT_ENTER);

        MY_SAFE_RELEASE(dxgiFactory);
    }

    // Create Framebuffer Render Target
    ID3D11RenderTargetView* dxRenderTargetView;
    {
        ID3D11Texture2D* dxBackBuffer = nullptr;
        HRESULT hr = dxSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&dxBackBuffer);
        MYASSERT(SUCCEEDED(hr));

        hr = dxDevice->CreateRenderTargetView(dxBackBuffer, 0, &dxRenderTargetView);
        MYASSERT(SUCCEEDED(hr));
        MY_SAFE_RELEASE(dxBackBuffer);
    }

    // Compile Vertex Shader
    ID3DBlob* vsBlob;
    ID3D11VertexShader* vertexShader;
    {
        ID3DBlob* shaderCompileErrorsBlob;
        HRESULT hr = D3DCompileFromFile(L"shaders.hlsl", nullptr, nullptr, "vs_main", "vs_5_0", 0, 0, &vsBlob, &shaderCompileErrorsBlob);
        if(FAILED(hr))
        {
            const char* errStr = nullptr;
            if(hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
            {
                errStr = "Could not compile Vertex shader; file not found";
            }
            else if(shaderCompileErrorsBlob) 
            {
                errStr = (const char*)shaderCompileErrorsBlob->GetBufferPointer();
                MY_SAFE_RELEASE(shaderCompileErrorsBlob);
            }

            myFatalError(errStr, "D3DCompileFromFile() - Vertex Shader compile failed");
            return 1;
        }

        hr = dxDevice->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), nullptr, &vertexShader);

        MYASSERT(SUCCEEDED(hr));
    }

    // Compile Pixel Shader
    ID3D11PixelShader* pixelShader;
    {
        ID3DBlob* psBlob;
        ID3DBlob* shaderCompileErrorsBlob;
        HRESULT hr = D3DCompileFromFile(L"shaders.hlsl", nullptr, nullptr, "ps_main", "ps_5_0", 0, 0, &psBlob, &shaderCompileErrorsBlob);
        if(FAILED(hr))
        {
            const char* errStr = nullptr;
            if(hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND))
            {
                errStr = "Could not compile Pixel shader; file not found";
            }
            else if(shaderCompileErrorsBlob) 
            {
                errStr = (const char*)shaderCompileErrorsBlob->GetBufferPointer();
                MY_SAFE_RELEASE(shaderCompileErrorsBlob);
            }

            myFatalError(errStr, "D3DCompileFromFile() - Pixel Shader compile failed");

            return 1;
        }

        hr = dxDevice->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), nullptr, &pixelShader);
        MYASSERT(SUCCEEDED(hr));
        MY_SAFE_RELEASE(psBlob);
    }

    // Define Input Layout - Count the number of floats per vertex, it is '7'
    ID3D11InputLayout* inputLayout;
    {
        D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
        {
            // SemanticName   SemanticIndex                          Format InputSlot             AlignedByteOffset                InputSlotClass InstanceDataStepRate 
            {         "POS",              0,    DXGI_FORMAT_R32G32B32_FLOAT,        0,                            0, D3D11_INPUT_PER_VERTEX_DATA,                    0 },
            {         "COL",              0, DXGI_FORMAT_R32G32B32A32_FLOAT,        0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,                    0 }
        };

        HRESULT hr = dxDevice->CreateInputLayout(inputElementDesc, ARRAYSIZE(inputElementDesc), vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &inputLayout);
        MYASSERT(SUCCEEDED(hr));
        MY_SAFE_RELEASE(vsBlob);
    }

    // Create Vertex Buffer

    // Vertices for the Shape
    float vertices[] = 
    { //   x,     y,    z,    r,   g,   b,   a
        0.0f,  0.5f,  0.f,  0.f, 1.f, 0.f, 1.f,
        0.5f, -0.5f,  0.f,  1.f, 0.f, 0.f, 1.f,
       -0.5f, -0.5f,  0.f,  0.f, 0.f, 1.f, 1.f
    };

    UINT stride = 7 * sizeof(float); // see layout above, and make sure this matches
    UINT numVert = sizeof(vertices) / stride;
    UINT vertOffset = 0;

    D3D11_BUFFER_DESC vertexBuffDesc = { 0 };
    vertexBuffDesc.ByteWidth = sizeof(vertices);
    vertexBuffDesc.Usage = D3D11_USAGE_IMMUTABLE;
    vertexBuffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vertexSubData = { 0 };
    vertexSubData.pSysMem = &vertices;

    ID3D11Buffer* vertexBuff;
    HRESULT hr = dxDevice->CreateBuffer(&vertexBuffDesc, &vertexSubData, &vertexBuff);
    MYASSERT(SUCCEEDED(hr));

    bool isRunning = true;

    // This is the main event loop for our window
    while(isRunning)
    {
        MSG msg = { 0 };

        // Check for new messages and get them handler with the windows procedures (which will be ours 'MyWndProc()', than eventually the default one.)
        while(PeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
        {
            if(msg.message == WM_QUIT)
            {
                isRunning = false;
            }

            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }

        // If the window is resizes, we need to adjust our swap chain
        if(_winResized)
        {
            // Unbind render target, release, and prepare for changes.
            dxDeviceContext->OMSetRenderTargets(0, 0, 0);
            MY_SAFE_RELEASE(dxRenderTargetView);
            dxDeviceContext->ClearState();
            dxDeviceContext->Flush();

            // Resize buffers in swap chain
            HRESULT res = dxSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);

            MYASSERT(SUCCEEDED(res));

            // Get the Back Buffer
            ID3D11Texture2D* dxBackBuffer = nullptr;
            res = dxSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&dxBackBuffer);
            MYASSERT(SUCCEEDED(res));

            // Create a New Render Target View
            res = dxDevice->CreateRenderTargetView(dxBackBuffer, 0, &dxRenderTargetView);
            MYASSERT(SUCCEEDED(res));

            MY_SAFE_RELEASE(dxBackBuffer);

            _winResized = false;
        }

        // Get the Window Rectangle corner positions - used later.
        RECT winRect;
        GetClientRect(hwnd, &winRect);

        // Clear render target with a background color
        FLOAT bgColor[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
        dxDeviceContext->ClearRenderTargetView(dxRenderTargetView, bgColor);

        // Set up elements of graphic pipeline.
        // For Reference, here is a picture of the graphics pipeline: https://docs.microsoft.com/en-us/windows/win32/direct3d11/overviews-direct3d-11-graphics-pipeline
        // * We are setting up the stages of the pipeline that we are using, in order of data flow.
        //   * This is not necessary; but we're doing it to make this example easier to follow referencing the above diagram.

        // Tell the Input Assembler (IA) that we are going to use a triangle list, the layout we defined, and about our vertex buffer.
        dxDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        dxDeviceContext->IASetInputLayout(inputLayout);
        dxDeviceContext->IASetVertexBuffers(0, 1, &vertexBuff, &stride, &vertOffset);

        // Tell the Device about the vertex shader we will use
        dxDeviceContext->VSSetShader(vertexShader, nullptr, 0);
 
        // Create a viewport from the Window Rectangle (RS = Rasterizer Stage)
        D3D11_VIEWPORT viewport = { 0.0f, 0.0f, (FLOAT)(winRect.right - winRect.left), (FLOAT)(winRect.bottom - winRect.top), 0.0f, 1.0f };
        dxDeviceContext->RSSetViewports(1, &viewport);

        // Tell the Device about the pixel shader we will use
        dxDeviceContext->PSSetShader(pixelShader, nullptr, 0);

        // Bind the render target for the Output Merger (OM)
        dxDeviceContext->OMSetRenderTargets(1, &dxRenderTargetView, nullptr);

        // Tell the device to do the draw.
        dxDeviceContext->Draw(numVert, 0);

        // Present via swap chain.
        dxSwapChain->Present(1, 0);
    }

    dxDeviceContext->ClearState();

    MY_SAFE_RELEASE(vertexBuff);
    MY_SAFE_RELEASE(inputLayout);
    MY_SAFE_RELEASE(vertexShader);
    MY_SAFE_RELEASE(pixelShader);
    MY_SAFE_RELEASE(dxRenderTargetView);
    MY_SAFE_RELEASE(dxSwapChain);
    MY_SAFE_RELEASE(dxDeviceContext);
    MY_SAFE_RELEASE(vsBlob);

#ifdef _DEBUG
    //d3dDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
    MY_SAFE_RELEASE(d3dDebug);
#endif
    MY_SAFE_RELEASE(dxDevice);

    return 0;
}