#include "Graphic.h"

bool Graphic::Init(HWND hWnd)
{
    EnableDebugLayer();
    if (!CreateDevice()) return false;
    if (!CreateCommandQueue()) return false;
    if (!CreateSwapChain(hWnd)) return false;
    if (!CreateRenderTarget()) return false;
    if (!CreateRootSignature()) return false;
    if (!CreatePipelineState()) return false;
    if (!CreateCommandList()) return false;
    if (!CreateFence()) return false;
    return true;
}

void Graphic::Render(Game* game)
{
    BeginRendering();
    game->Draw();
    EndRendering();
}

void Graphic::Release()
{
    FlushGPU();

    if (m_pDevice)
    {
        m_pDevice->Release();
        m_pDevice = nullptr;
    }
    if (m_pCommandQueue)
    {
        m_pCommandQueue->Release();
        m_pCommandQueue = nullptr;
    }
    if (m_pSwapChain)
    {
        m_pSwapChain->Release();
        m_pSwapChain = nullptr;
    }
    if (m_pFactory)
    {
        m_pFactory->Release();
        m_pFactory = nullptr;
    }
    if (m_pRenderTargetHeap)
    {
        m_pRenderTargetHeap->Release();
        m_pRenderTargetHeap = nullptr;
    }
    for (int i = 0; i < BACK_BUFFER_NUM; ++i)
    {
        if (m_pRenderTargets[i])
        {
            m_pRenderTargets[i]->Release();
            m_pRenderTargets[i] = nullptr;
        }
    }
    if (m_pCommandAllocator)
    {
        m_pCommandAllocator->Release();
        m_pCommandAllocator = nullptr;
    }
    if (m_pCommandList)
    {
        m_pCommandList->Release();
        m_pCommandList = nullptr;
    }
    if (m_pFence)
    {
        m_pFence->Release();
        m_pFence = nullptr;
    }
    if (m_pRootSignature)
    {
        m_pRootSignature->Release();
        m_pRootSignature = nullptr;
    }
    if (m_pPipelineState)
    {
        m_pPipelineState->Release();
        m_pPipelineState = nullptr;
    }
}

bool Graphic::CreateDevice()
{
    // デバイスを作成
    HRESULT hr = D3D12CreateDevice(
        nullptr,
        D3D_FEATURE_LEVEL_11_0,
        IID_PPV_ARGS(&m_pDevice)
    );

    if (FAILED(hr))
        return false;

    return true;
}

bool Graphic::CreateCommandQueue()
{
    // コマンドキューの設定
    D3D12_COMMAND_QUEUE_DESC cqDesc = {};
    cqDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    cqDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    cqDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

    // コマンドキューを作成
    HRESULT hr = m_pDevice->CreateCommandQueue(
        &cqDesc,
        IID_PPV_ARGS(&m_pCommandQueue)
    );

    if (FAILED(hr))
        return false;

    return true;
}

bool Graphic::CreateSwapChain(HWND hWnd)
{
    HRESULT hr;

    // DXGIファクトリを作成
    hr = CreateDXGIFactory1(IID_PPV_ARGS(&m_pFactory));

    if (FAILED(hr))
        return false;

    // スワップチェーンの設定
    DXGI_SWAP_CHAIN_DESC1 desc = {};
    desc.Width = WINDOW_WIDTH;
    desc.Height = WINDOW_HEIGHT;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.Stereo = false;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
    desc.BufferCount = BACK_BUFFER_NUM;
    desc.Scaling = DXGI_SCALING_STRETCH;
    desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    desc.Flags = 0;

    // スワップチェーンを作成
    hr = m_pFactory->CreateSwapChainForHwnd(
        m_pCommandQueue,
        hWnd,
        &desc,
        nullptr,
        nullptr,
        (IDXGISwapChain1**)&m_pSwapChain
    );

    if (FAILED(hr))
        return false;

    // 現在のバックバッファーインデックス
    m_FrameIndex = m_pSwapChain->GetCurrentBackBufferIndex();

    return true;
}

bool Graphic::CreateRenderTarget()
{
    // ディスクリプタヒープの設定
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
    heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    heapDesc.NumDescriptors = BACK_BUFFER_NUM;
    heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

    // ディスクリプタヒープを作成
    HRESULT hr = m_pDevice->CreateDescriptorHeap(
        &heapDesc,
        IID_PPV_ARGS(&m_pRenderTargetHeap)
    );

    if (FAILED(hr))
        return false;

    // ハンドルのインクリメントサイズを取得
    m_RTVIncrementSize = m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    // ヒープの先頭ハンドルを取得
    D3D12_CPU_DESCRIPTOR_HANDLE handle = m_pRenderTargetHeap->GetCPUDescriptorHandleForHeapStart();

    for (int i = 0; i < BACK_BUFFER_NUM; ++i)
    {
        // スワップチェーンのバッファーを取得
        m_pSwapChain->GetBuffer(i, IID_PPV_ARGS(&m_pRenderTargets[i]));

        // レンダーターゲットビューを作成
        m_pDevice->CreateRenderTargetView(
            m_pRenderTargets[i],
            nullptr,
            handle
        );

        // 次へずらす
        handle.ptr += m_RTVIncrementSize;
    }

    return true;
}

bool Graphic::CreateCommandList()
{
    HRESULT hr;

    // コマンドアロケータを作成
    hr = m_pDevice->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(&m_pCommandAllocator)
    );

    if (FAILED(hr))
        return false;

    // コマンドリストを作成
    hr = m_pDevice->CreateCommandList(
        0,
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        m_pCommandAllocator,
        m_pPipelineState,
        IID_PPV_ARGS(&m_pCommandList)
    );

    if (FAILED(hr))
        return false;

    m_pCommandList->Close();

    return true;
}

bool Graphic::CreateFence()
{
    // フェンスを作成
    HRESULT hr = m_pDevice->CreateFence(
        0,
        D3D12_FENCE_FLAG_NONE,
        IID_PPV_ARGS(&m_pFence)
    );

    if (FAILED(hr))
        return false;

    // イベントの生成
    m_FenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    m_FenceValue = 1;

    return true;
}

bool Graphic::CreateRootSignature()
{
    HRESULT hr;

    // ルートシグネチャの設定
    D3D12_ROOT_SIGNATURE_DESC desc = {};
    desc.NumParameters = 0;
    desc.pParameters = nullptr;
    desc.NumStaticSamplers = 0;
    desc.pStaticSamplers = nullptr;
    desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

    ID3DBlob* pSignature;
    ID3DBlob* pError;

    // シリアル化
    hr = D3D12SerializeRootSignature(
        &desc,
        D3D_ROOT_SIGNATURE_VERSION_1,
        &pSignature,
        &pError
    );

    if (FAILED(hr))
        return false;

    // ルートシグネチャの作成
    hr = m_pDevice->CreateRootSignature(
        0,
        pSignature->GetBufferPointer(),
        pSignature->GetBufferSize(),
        IID_PPV_ARGS(&m_pRootSignature)
    );

    if (FAILED(hr))
        return false;

    return true;
}

bool Graphic::CreatePipelineState()
{
    HRESULT hr;
    ID3DBlob* pVertexShader;
    ID3DBlob* pPixelShader;
    ID3DBlob* pError;

#ifdef _DEBUG
    UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
    UINT compileFlags = 0;
#endif

    // 頂点シェーダーをコンパイル
    hr = D3DCompileFromFile(
        L"Assets/Shader/VertexShader.hlsl",
        nullptr,
        nullptr,
        "VSMain",
        "vs_5_0",
        compileFlags,
        0,
        &pVertexShader,
        &pError
    );

    if (FAILED(hr))
        return false;

    // ピクセルシェーダーをコンパイル
    hr = D3DCompileFromFile(
        L"Assets/Shader/PixelShader.hlsl",
        nullptr,
        nullptr,
        "PSMain",
        "ps_5_0",
        compileFlags,
        0,
        &pPixelShader,
        &pError
    );

    if (FAILED(hr))
        return false;

    // レンド状態の設定
    D3D12_RENDER_TARGET_BLEND_DESC defaultRenderTargetBlendDesc =
    {
        FALSE,
        FALSE,
        D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
        D3D12_BLEND_ONE, D3D12_BLEND_ZERO, D3D12_BLEND_OP_ADD,
        D3D12_LOGIC_OP_NOOP,
        D3D12_COLOR_WRITE_ENABLE_ALL,
    };

    // 入力アセンブラーの設定
    D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
    {
        {
            "POSITION",
            0,
            DXGI_FORMAT_R32G32B32_FLOAT,
            0,
            0,
            D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
            0
        },
        {
            "COLOR",
            0,
            DXGI_FORMAT_R32G32B32A32_FLOAT,
            0,
            12,
            D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,
            0
        },
    };

    // グラフィックスパイプラインの設定
    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
    psoDesc.pRootSignature = m_pRootSignature;
    psoDesc.VS.pShaderBytecode = pVertexShader->GetBufferPointer();
    psoDesc.VS.BytecodeLength = pVertexShader->GetBufferSize();
    psoDesc.PS.pShaderBytecode = pPixelShader->GetBufferPointer();
    psoDesc.PS.BytecodeLength = pPixelShader->GetBufferSize();
    psoDesc.StreamOutput.pSODeclaration = nullptr;
    psoDesc.StreamOutput.NumEntries = 0;
    psoDesc.StreamOutput.pBufferStrides = nullptr;
    psoDesc.StreamOutput.NumStrides = 0;
    psoDesc.StreamOutput.RasterizedStream = 0;
    psoDesc.BlendState.AlphaToCoverageEnable = FALSE;
    psoDesc.BlendState.IndependentBlendEnable = FALSE;
    for (UINT i = 0; i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i) {
        psoDesc.BlendState.RenderTarget[i] = defaultRenderTargetBlendDesc;
    }
    psoDesc.SampleMask = D3D12_DEFAULT_SAMPLE_MASK;
    psoDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
    psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
    psoDesc.RasterizerState.FrontCounterClockwise = FALSE;
    psoDesc.RasterizerState.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
    psoDesc.RasterizerState.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
    psoDesc.RasterizerState.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
    psoDesc.RasterizerState.DepthClipEnable = TRUE;
    psoDesc.RasterizerState.MultisampleEnable = FALSE;
    psoDesc.RasterizerState.AntialiasedLineEnable = FALSE;
    psoDesc.RasterizerState.ForcedSampleCount = 0;
    psoDesc.RasterizerState.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
    psoDesc.DepthStencilState.DepthEnable = FALSE;
    psoDesc.DepthStencilState.StencilEnable = FALSE;
    psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
    psoDesc.IBStripCutValue = D3D12_INDEX_BUFFER_STRIP_CUT_VALUE_DISABLED;
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psoDesc.NumRenderTargets = 1;
    psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
    psoDesc.DSVFormat = DXGI_FORMAT_UNKNOWN;
    psoDesc.SampleDesc.Count = 1;
    psoDesc.SampleDesc.Quality = 0;
    psoDesc.NodeMask = 0;
    psoDesc.CachedPSO.pCachedBlob = nullptr;
    psoDesc.CachedPSO.CachedBlobSizeInBytes = 0;
    psoDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;

    // グラフィックスパイプラインステートを作成
    hr = m_pDevice->CreateGraphicsPipelineState(
        &psoDesc,
        IID_PPV_ARGS(&m_pPipelineState)
    );

    if (FAILED(hr))
        return false;

    // シェーダーを解放
    if (pVertexShader)
        pVertexShader->Release();
    if (pPixelShader)
        pPixelShader->Release();
    if (pError)
        pError->Release();

    return true;
}

void Graphic::BeginRendering()
{
    // ビューポートの設定
    m_Viewport = {};
    m_Viewport.Width = static_cast<FLOAT>(WINDOW_WIDTH);
    m_Viewport.Height = static_cast<FLOAT>(WINDOW_HEIGHT);
    m_Viewport.MaxDepth = 1.0f;

    // シザーの設定
    m_ScissorRect = {};
    m_ScissorRect.right = WINDOW_WIDTH;
    m_ScissorRect.bottom = WINDOW_HEIGHT;

    // コマンドをリセット
    m_pCommandAllocator->Reset();
    m_pCommandList->Reset(m_pCommandAllocator, m_pPipelineState);
    m_pCommandList->SetGraphicsRootSignature(m_pRootSignature);
    m_pCommandList->RSSetViewports(1, &m_Viewport);
    m_pCommandList->RSSetScissorRects(1, &m_ScissorRect);

    // リソースバリアの設定
    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;                      // リソースバリアの種類を指定
    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;                           // 分割リソースバリアを設定
    barrier.Transition.pResource = m_pRenderTargets[m_FrameIndex];              // 遷移で使用されるリソースへのポインター
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;   // 遷移のサブリソースのインデックス
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;              // サブリソース
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;         // サブリソース

    // バリアをコマンドリストに記録する
    m_pCommandList->ResourceBarrier(1, &barrier);

    // バックバッファ用のハンドルを計算
    D3D12_CPU_DESCRIPTOR_HANDLE handle = m_pRenderTargetHeap->GetCPUDescriptorHandleForHeapStart();
    handle.ptr += m_FrameIndex * m_RTVIncrementSize;

    // レンダーターゲットをクリア
    const float color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    m_pCommandList->ClearRenderTargetView(handle, color, 0, nullptr);
}

void Graphic::EndRendering()
{
    // リソースバリアの設定
    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource = m_pRenderTargets[m_FrameIndex];
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;

    // バリアをコマンドリストに記録する
    m_pCommandList->ResourceBarrier(1, &barrier);

    // コマンドリストのを閉じて実行キューを贈る
    m_pCommandList->Close();
    ID3D12CommandList* commandLists[] = { m_pCommandList };
    m_pCommandQueue->ExecuteCommandLists(_countof(commandLists), commandLists);

    // スワップチェーンで画面を表示
    m_pSwapChain->Present(1, 0);

    // GPU完了待ち
    FlushGPU();

    // 次のバックバッファインデックスを取得
    m_FrameIndex = m_pSwapChain->GetCurrentBackBufferIndex();
}

void Graphic::FlushGPU()
{
    const UINT64 fence = m_FenceValue++;
    m_pCommandQueue->Signal(m_pFence, fence);
    if (m_pFence->GetCompletedValue() < fence) {
        m_pFence->SetEventOnCompletion(fence, m_FenceEvent);
        WaitForSingleObject(m_FenceEvent, INFINITE);
    }
}

void Graphic::EnableDebugLayer()
{
#ifdef _DEBUG
    ID3D12Debug* pDebugLayer;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&pDebugLayer))))
    {
        pDebugLayer->EnableDebugLayer();
        pDebugLayer->Release();
    }
#endif
}
