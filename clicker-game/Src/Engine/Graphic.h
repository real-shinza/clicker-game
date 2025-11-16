#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "Window.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <directxmath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

using namespace DirectX;

class Graphic
{
public:
    /// <summary>
    /// グラフィック初期化
    /// </summary>
    bool Init();

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

    /// <summary>
    /// シェーダーを作成
    /// </summary>
    bool CreateShader();

    /// <summary>
    /// バッファを作成
    /// </summary>
    bool CreateBuffer();

    /// <summary>
    /// サンプラーステートを作成
    /// </summary>
    bool CreateSamplerState();

public:
    /// <summary>
    /// 描画開始処理
    /// </summary>
    void BeginRendering();

    /// <summary>
    /// 描画終了処理
    /// </summary>
    void EndRendering();

private:
    ID3D11Device* m_pDevice;
    ID3D11DeviceContext* m_pContext;
    IDXGISwapChain* m_pSwapChain;
    ID3D11RenderTargetView* m_pRenderTargetView;
    ID3D11VertexShader* m_pVertexShader;
    ID3D11PixelShader* m_pPixelShader;
    ID3D11InputLayout* m_pInputLayout;
    ID3D11Buffer* m_pVertexBuffer;
    ID3D11Buffer* m_pConstantBuffer;
    ID3D11SamplerState* m_pSamplerState;
    ID3D11ShaderResourceView* m_pShaderResourceView;
};

#endif
