#include "Graphic.h"

bool Graphic::Init()
{
    if (!CreateDeviceAndSwapChain()) return false;
    if (!CreateRenderTargetView()) return false;
    return true;
}

void Graphic::BeginRendering()
{
    const float color[] = { 0.0f, 1.0f, 1.0f, 1.0f };
    m_pContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);
    m_pContext->ClearRenderTargetView(m_pRenderTargetView, color);
}

void Graphic::EndRendering()
{
    m_pSwapChain->Present(1, 0);
}

void Graphic::Release()
{
    if (m_pRenderTargetView)
    {
        m_pRenderTargetView->Release();
        m_pRenderTargetView = nullptr;
    }

    if (m_pSwapChain)
    {
        m_pSwapChain->Release();
        m_pSwapChain = nullptr;
    }

    if (m_pContext)
    {
        m_pContext->Release();
        m_pContext = nullptr;
    }

    if (m_pDevice)
    {
        m_pDevice->Release();
        m_pDevice = nullptr;
    }
}

bool Graphic::CreateDeviceAndSwapChain()
{
    // ウィンドウハンドルを取得
    HWND hWnd = FindWindow(L"Clicker Game", nullptr);

    // スワップチェーンの設定
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
    swapChainDesc.BufferDesc.Width = Window::WINDOW_WIDTH;
    swapChainDesc.BufferDesc.Height = Window::WINDOW_HEIGHT;
    swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 1;
    swapChainDesc.OutputWindow = hWnd;
    swapChainDesc.Windowed = true;

    // デバイスとスワップチェーンを作成
    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        &m_pSwapChain,
        &m_pDevice,
        nullptr,
        &m_pContext
    );

    if (FAILED(hr))
        return false;

    return true;
}

bool Graphic::CreateRenderTargetView()
{
    // ビューポートの設定
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(viewport));
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = Window::WINDOW_WIDTH;
    viewport.Height = Window::WINDOW_HEIGHT;
    viewport.MinDepth = D3D11_MIN_DEPTH;
    viewport.MaxDepth = D3D11_MAX_DEPTH;
    m_pContext->RSSetViewports(1, &viewport);

    // バックバッファを作成
    ID3D11Texture2D* backBuffer;
    if (FAILED(m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer))))
        return false;
    if (FAILED(m_pDevice->CreateRenderTargetView(backBuffer, nullptr, &m_pRenderTargetView)))
        return false;

    return true;
}
