#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <d3d12.h>
#include <dxgi1_6.h>
#include "../Game/Game.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

class Graphic
{
public:
    Graphic();
    ~Graphic();

    /// <summary>
    /// レンダリング初期化
    /// </summary>
    void Init(HWND hWnd);

    /// <summary>
    /// レンダリング更新
    /// </summary>
    void Update(Game* game);

    /// <summary>
    /// レンダリング解放
    /// </summary>
    void Release();

private:
    /// <summary>
    /// デバイス作成
    /// </summary>
    void CreateDevice();

    /// <summary>
    /// コマンドキュー作成
    /// </summary>
    void CreateCommandQueue();

    /// <summary>
    /// スワップチェーン作成
    /// </summary>
    void CreateSwapChain(HWND hWnd);

    /// <summary>
    /// レンダーターゲット作成
    /// </summary>
    void CreateRenderTarget();

    /// <summary>
    /// コマンドリスト作成
    /// </summary>
    void CreateCommandList();

    /// <summary>
    /// フェンス作成
    /// </summary>
    void CreateFence();

    /// <summary>
    /// コマンドをリセット
    /// </summary>
    void ResetCommand();

    /// <summary>
    /// レンダーターゲット設定
    /// </summary>
    void SetRenderTarget();

    /// <summary>
    /// コマンド実行
    /// </summary>
    void ExecuteCommand();

private:
    static const int BACK_BUFFER_NUM = 2;

    ID3D12Device* m_pDevice;
    ID3D12CommandQueue* m_pCommandQueue;
    IDXGISwapChain3* m_pSwapChain;
    IDXGIFactory7* m_pFactory;
    UINT m_FrameIndex;
    ID3D12DescriptorHeap* m_pRenderTargetHeap;
    UINT m_RTVIncrementSize;
    ID3D12Resource* m_pRenderTargets[BACK_BUFFER_NUM];
    ID3D12CommandAllocator* m_pCommandAllocator;
    ID3D12GraphicsCommandList* m_pCommandList;
    ID3D12Fence* m_pFence;
    HANDLE m_FenceEvent;
    UINT64 m_FenceValue;
};

#endif
