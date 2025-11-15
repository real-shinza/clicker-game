#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "Window.h"
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

class Graphic
{
public:
    /// <summary>
    /// グラフィック初期化
    /// </summary>
    bool Init();

    /// <summary>
    /// 描画開始処理
    /// </summary>
    void BeginRendering();

    /// <summary>
    /// 描画終了処理
    /// </summary>
    void EndRendering();

    /// <summary>
    /// グラフィック解放
    /// </summary>
    void Release();

private:
    /// <summary>
    /// デバイスとスワップチェーンを作成
    /// </summary>
    bool CreateDeviceAndSwapChain();

    /// <summary>
    /// レンダーターゲットビューを作成
    /// </summary>
    bool CreateRenderTargetView();

private:
    ID3D11Device* m_pDevice;
    ID3D11DeviceContext* m_pContext;
    IDXGISwapChain* m_pSwapChain;
    ID3D11RenderTargetView* m_pRenderTargetView;
};

#endif
