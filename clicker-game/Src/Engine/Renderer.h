#ifndef RENDERER_H
#define RENDERER_H

#include <d3d12.h>
#include <dxgi1_6.h>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    /// <summary>
    /// レンダリング初期化
    /// </summary>
    void Init(HWND hWnd);

    /// <summary>
    /// レンダリング更新
    /// </summary>
    void Update();

    /// <summary>
    /// レンダリング解放
    /// </summary>
    void Release();

private:
    ID3D12Device* m_Device;
    IDXGISwapChain3* m_SwapChain;
};

#endif
