#include "Graphic.h"

bool Graphic::Init(HWND hWnd)
{
    if (!CreateDevice()) return false;
    if (!CreateCommandQueue()) return false;
    if (!CreateSwapChain(hWnd)) return false;
    if (!CreateRenderTarget()) return false;
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

bool Graphic::CreateDevice()
{
    // デバイスを作成
    HRESULT hr = D3D12CreateDevice(
        nullptr,                    // ビデオアダプターへのポインター
        D3D_FEATURE_LEVEL_11_0,     // 最低要求機能レベル
        IID_PPV_ARGS(&m_pDevice)    // 出力デバイスポインター
    );

    if (FAILED(hr))
        return false;
    return true;
}

bool Graphic::CreateCommandQueue()
{
    // コマンドキューの設定
    D3D12_COMMAND_QUEUE_DESC cqDesc = {};
    cqDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;           // タイプを指定
    cqDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;  // コマンドキューの優先順位
    cqDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;           // フラグを指定

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
    desc.Width = WINDOW_WIDTH;                          // 解像度の幅
    desc.Height = WINDOW_HEIGHT;                        // 解像度の高さ
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;           // 表示形式
    desc.Stereo = false;                                // ステレオ
    desc.SampleDesc.Count = 1;                          // マルチサンプルの数
    desc.SampleDesc.Quality = 0;                        // イメージの品質レベル
    desc.BufferUsage = DXGI_USAGE_BACK_BUFFER;          // バックバッファーのサーフェス使用量
    desc.BufferCount = BACK_BUFFER_NUM;                 // バックバッファーの数
    desc.Scaling = DXGI_SCALING_STRETCH;                // スケーリング方法
    desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;    // プレゼンテーションモデル
    desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;       // バックバッファーの透過性の動作を識別
    desc.Flags = 0;                                     // フラグ

    // スワップチェーンを作成
    hr = m_pFactory->CreateSwapChainForHwnd(
        m_pCommandQueue,                    // コマンドキューへのポインター
        hWnd,                               // HWNDハンドル
        &desc,                              // スワップチェーンの設定
        nullptr,                            // 全画面表示スワップチェーンへのポインター
        nullptr,                            // 出力のインターフェイスへのポインター
        (IDXGISwapChain1**)&m_pSwapChain    // スワップチェーンのインターフェイスへのポインター
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
    heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;     // 記述子の型を指定
    heapDesc.NumDescriptors = BACK_BUFFER_NUM;          // 記述子の数
    heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;   // オプションを指定

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
        nullptr,
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

void Graphic::BeginRendering()
{
    // コマンドをリセット
    m_pCommandAllocator->Reset();
    m_pCommandList->Reset(m_pCommandAllocator, nullptr);

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
    // コマンドリストのを閉じて実行キューを贈る
    m_pCommandList->Close();
    ID3D12CommandList* commandLists[] = { m_pCommandList };
    m_pCommandQueue->ExecuteCommandLists(_countof(commandLists), commandLists);

    // スワップチェーンで画面を表示
    m_pSwapChain->Present(1, 0);

    // 次のバックバッファインデックスを取得
    m_FrameIndex = m_pSwapChain->GetCurrentBackBufferIndex();
}
