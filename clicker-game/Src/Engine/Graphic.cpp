#include "Graphic.h"

Graphic::Graphic()
{
}

Graphic::~Graphic()
{
}

void Graphic::Init(HWND hWnd)
{
    CreateDevice();
    CreateCommandQueue();
    CreateSwapChain(hWnd);
    CreateRenderTarget();
    CreateCommandList();
    CreateFence();
}

void Graphic::Update()
{
    ResetCommand();
    SetRenderTarget();
    ExecuteCommand();
}

void Graphic::Release()
{
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
}

void Graphic::CreateDevice()
{
    D3D12CreateDevice(
        nullptr,
        D3D_FEATURE_LEVEL_11_0,
        IID_PPV_ARGS(&m_pDevice)
    );
}

void Graphic::CreateCommandQueue()
{
    D3D12_COMMAND_QUEUE_DESC cqDesc = {};
    cqDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    cqDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
    cqDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

    // キューの作成
    m_pDevice->CreateCommandQueue(
        &cqDesc,
        IID_PPV_ARGS(&m_pCommandQueue)
    );
}

void Graphic::CreateSwapChain(HWND hWnd)
{
    // 設定
    CreateDXGIFactory1(IID_PPV_ARGS(&m_pFactory));
    DXGI_SWAP_CHAIN_DESC1 desc = {};
    desc.BufferCount = BACK_BUFFER_NUM;
    desc.BufferUsage = DXGI_USAGE_BACK_BUFFER;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.Width = 800;
    desc.Height = 600;
    desc.Stereo = false;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Scaling = DXGI_SCALING_STRETCH;
    desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    desc.Flags = 0;

    // スワップチェーン作成
    m_pFactory->CreateSwapChainForHwnd(
        m_pCommandQueue,
        hWnd,
        &desc,
        nullptr,
        nullptr,
        (IDXGISwapChain1**)&m_pSwapChain
    );

    // 現在のバックバッファーインデックス
    m_FrameIndex = m_pSwapChain->GetCurrentBackBufferIndex();
}

void Graphic::CreateRenderTarget()
{
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
    heapDesc.NumDescriptors = BACK_BUFFER_NUM;
    heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

    // ディスクリプタヒープ作成
    m_pDevice->CreateDescriptorHeap(
        &heapDesc,
        IID_PPV_ARGS(&m_pRenderTargetHeap)
    );
    m_RTVIncrementSize = m_pDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    D3D12_CPU_DESCRIPTOR_HANDLE handle = m_pRenderTargetHeap->GetCPUDescriptorHandleForHeapStart();

    for (int i = 0; i < BACK_BUFFER_NUM; ++i)
    {
        // スワップチェーンのバッファーを取得
        m_pSwapChain->GetBuffer(i, IID_PPV_ARGS(&m_pRenderTargets[i]));

        // レンダーターゲットビューの作成
        m_pDevice->CreateRenderTargetView(
            m_pRenderTargets[i],
            nullptr,
            handle
        );

        // 次へずらす
        handle.ptr += m_RTVIncrementSize;
    }
}

void Graphic::CreateCommandList()
{
    // コマンドアロケータ作成
    m_pDevice->CreateCommandAllocator(
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        IID_PPV_ARGS(&m_pCommandAllocator)
    );

    // コマンドリストの作成
    m_pDevice->CreateCommandList(
        0,
        D3D12_COMMAND_LIST_TYPE_DIRECT,
        m_pCommandAllocator,
        nullptr,
        IID_PPV_ARGS(&m_pCommandList)
    );
    m_pCommandList->Close();
}

void Graphic::CreateFence()
{
    // フェンス作成
    m_pDevice->CreateFence(
        0,
        D3D12_FENCE_FLAG_NONE,
        IID_PPV_ARGS(&m_pFence)
    );
    m_FenceValue = 1;

    // イベントの生成
    m_FenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
}

void Graphic::ResetCommand()
{
    m_pCommandAllocator->Reset();
    m_pCommandList->Reset(m_pCommandAllocator, nullptr);
}

void Graphic::SetRenderTarget()
{
    // リソースバリアの設定
    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource = m_pRenderTargets[m_FrameIndex];
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

    // バリアをコマンドリストに記録する
    m_pCommandList->ResourceBarrier(1, &barrier);

    D3D12_CPU_DESCRIPTOR_HANDLE handle = m_pRenderTargetHeap->GetCPUDescriptorHandleForHeapStart();
    handle.ptr += m_FrameIndex * m_RTVIncrementSize;

    // レンダーターゲットをクリア
    float color[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    m_pCommandList->ClearRenderTargetView(handle, color, 0, nullptr);
}

void Graphic::ExecuteCommand()
{
    // リソースバリアの設定
    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource = m_pRenderTargets[m_FrameIndex];
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    m_pCommandList->ResourceBarrier(1, &barrier);

    // コマンドリストのクローズと実行
    m_pCommandList->Close();
    ID3D12CommandList* commandLists[] = { m_pCommandList };
    m_pCommandQueue->ExecuteCommandLists(_countof(commandLists), commandLists);

    // 画面交換
    m_pSwapChain->Present(1, 0);

    // インデックスを更新
    m_FrameIndex = m_pSwapChain->GetCurrentBackBufferIndex();
}
