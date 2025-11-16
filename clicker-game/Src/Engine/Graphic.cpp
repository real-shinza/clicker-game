#include "Graphic.h"

bool Graphic::Init()
{
    if (!CreateDeviceAndSwapChain()) return false;
    if (!CreateRenderTargetView()) return false;
    if (!CreateShader()) return false;
    if (!CreateBuffer()) return false;
    if (!CreateSamplerState()) return false;
    return true;
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

    if (m_pVertexShader)
    {
        m_pVertexShader->Release();
        m_pVertexShader = nullptr;
    }

    if (m_pPixelShader)
    {
        m_pPixelShader->Release();
        m_pPixelShader = nullptr;
    }

    if (m_pInputLayout)
    {
        m_pInputLayout->Release();
        m_pInputLayout = nullptr;
    }

    if (m_pVertexBuffer)
    {
        m_pVertexBuffer->Release();
        m_pVertexBuffer = nullptr;
    }

    if (m_pConstantBuffer)
    {
        m_pConstantBuffer->Release();
        m_pConstantBuffer = nullptr;
    }

    if (m_pSamplerState)
    {
        m_pSamplerState->Release();
        m_pSamplerState = nullptr;
    }
}

bool Graphic::CreateDeviceAndSwapChain()
{
    // ウィンドウハンドルを取得
    HWND hWnd = FindWindow(Window::CLASS_NAME, nullptr);

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
    HRESULT hr;
    hr = m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    if (FAILED(hr))
        return false;
    hr = m_pDevice->CreateRenderTargetView(backBuffer, nullptr, &m_pRenderTargetView);
    if (FAILED(hr))
        return false;

    // レンダーターゲットをバックバッファに設定
    m_pContext->OMSetRenderTargets(1, &m_pRenderTargetView, nullptr);

    return true;
}

bool Graphic::CreateShader()
{
    ID3DBlob* pVertexShader;
    ID3DBlob* pPixelShader;
    HRESULT hr;
    ID3DBlob* errorBlob = nullptr;

    // 頂点シェーダーをコンパイル
    hr = D3DX11CompileFromFile(
        L"Assets/Shader/VertexShader.hlsl",
        nullptr,
        nullptr,
        "VSMain",
        "vs_4_0",
        0,
        0,
        nullptr,
        &pVertexShader,
        nullptr,
        nullptr
    );
    if (FAILED(hr))
        return false;

    // ピクセルシェーダーをコンパイル
    hr = D3DX11CompileFromFile(
        L"Assets/Shader/PixelShader.hlsl",
        nullptr,
        nullptr,
        "PSMain",
        "ps_4_0",
        0,
        0,
        nullptr,
        &pPixelShader,
        nullptr,
        nullptr
    );
    if (FAILED(hr))
        return false;

    // カプセル化
    hr = m_pDevice->CreateVertexShader(pVertexShader->GetBufferPointer(), pVertexShader->GetBufferSize(), nullptr, &m_pVertexShader);
    if (FAILED(hr))
        return false;
    hr = m_pDevice->CreatePixelShader(pPixelShader->GetBufferPointer(), pPixelShader->GetBufferSize(), nullptr, &m_pPixelShader);
    if (FAILED(hr))
        return false;
    
    // 頂点インプットレイアウトを定義
    D3D11_INPUT_ELEMENT_DESC inputElementDescs[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(float) * 4, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(float) * 8, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    
    // 頂点インプットレイアウトを作成
    hr = m_pDevice->CreateInputLayout(
        inputElementDescs,
        ARRAYSIZE(inputElementDescs),
        pVertexShader->GetBufferPointer(),
        pVertexShader->GetBufferSize(),
        &m_pInputLayout
    );
    if (FAILED(hr))
        return false;
    
    m_pContext->IASetInputLayout(m_pInputLayout);

    return true;
}

bool Graphic::CreateBuffer()
{
    HRESULT hr;

    // 頂点バッファの設定
    D3D11_BUFFER_DESC vbDesc = {};
    ZeroMemory(&vbDesc, sizeof(vbDesc));
    vbDesc.Usage = D3D11_USAGE_DYNAMIC;
    vbDesc.ByteWidth = sizeof(float) * (4 + 4 + 2) * 6;
    vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    // 頂点バッファを作成
    hr = m_pDevice->CreateBuffer(&vbDesc, nullptr, &m_pVertexBuffer);
    if (FAILED(hr))
        return false;

    // 定数バッファの設定
    D3D11_BUFFER_DESC cbDesc = {};
    ZeroMemory(&cbDesc, sizeof(cbDesc));
    cbDesc.Usage = D3D11_USAGE_DEFAULT;
    cbDesc.ByteWidth = sizeof(XMMATRIX);
    cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    // 定数バッファを作成
    hr = m_pDevice->CreateBuffer(&cbDesc, nullptr, &m_pConstantBuffer);
    if (FAILED(hr))
        return false;

    // 行列を作成
    XMMATRIX ortho = XMMatrixOrthographicOffCenterLH(0.0f, Window::WINDOW_WIDTH, Window::WINDOW_HEIGHT, 0.0f, 0.0f, 1.0f);
    ortho = XMMatrixTranspose(ortho);
    m_pContext->UpdateSubresource(m_pConstantBuffer, 0, nullptr, &ortho, 0, 0);

    return true;
}

bool Graphic::CreateSamplerState()
{
    // サンプラーステートの設定
    D3D11_SAMPLER_DESC samplerDesc = {};
    ZeroMemory(&samplerDesc, sizeof(samplerDesc));
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;

    // サンプラーステートを作成
    HRESULT hr = m_pDevice->CreateSamplerState(&samplerDesc, &m_pSamplerState);
    if (FAILED(hr))
        return false;

    return true;
}

void Graphic::BeginRendering()
{
    const float color[] = { 0.9f, 0.9f, 0.9f, 1.0f };
    m_pContext->ClearRenderTargetView(m_pRenderTargetView, color);
}

void Graphic::EndRendering()
{
    m_pSwapChain->Present(1, 0);
}
