#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <d3d12.h>
#include <d3dcompiler.h>
#include <dxgi1_6.h>
#include "../Game/Game.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")

class Graphic
{
public:
    /// <summary>
    /// グラフィック初期化
    /// </summary>
    bool Init(HWND hWnd);

    /// <summary>
    /// グラフィック更新
    /// </summary>
    void Render(Game* game);

    /// <summary>
    /// グラフィック解放
    /// </summary>
    void Release();

private:
    /// <summary>
    /// デバイス作成
    /// </summary>
    bool CreateDevice();

    /// <summary>
    /// コマンドキュー作成
    /// </summary>
    bool CreateCommandQueue();

    /// <summary>
    /// スワップチェーン作成
    /// </summary>
    bool CreateSwapChain(HWND hWnd);

    /// <summary>
    /// レンダーターゲット作成
    /// </summary>
    bool CreateRenderTarget();

    /// <summary>
    /// コマンドリスト作成
    /// </summary>
    bool CreateCommandList();

    /// <summary>
    /// フェンス作成
    /// </summary>
    bool CreateFence();

    /// <summary>
    /// ルートシグネチャ作成
    /// </summary>
    bool CreateRootSignature();

    /// <summary>
    /// パイプラインステート作成
    /// </summary>
    bool CreatePipelineState();

    /// <summary>
    /// 描画開始処理
    /// </summary>
    void BeginRendering();

    /// <summary>
    /// 描画終了処理
    /// </summary>
    void EndRendering();

    /// <summary>
    /// GPU完了を待つ
    /// </summary>
    void FlushGPU();

    /// <summary>
    /// デバッグレイヤー
    /// </summary>
    void EnableDebugLayer();

private:
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 600;
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
    ID3D12RootSignature* m_pRootSignature;
    ID3D12PipelineState* m_pPipelineState;
    D3D12_VIEWPORT m_Viewport;
    D3D12_RECT m_ScissorRect;
};

#endif
