#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "Window.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <d2d1.h>
#include <dwrite.h>
#include <directxmath.h>
#include <string>
#include <map>
#include <unordered_map>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib,"d2d1.lib")    
#pragma comment(lib,"dwrite.lib")

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
    /// 頂点バッファを作成
    /// </summary>
    bool CreateVertexBuffer();

    /// <summary>
    /// インデックスバッファを作成
    /// </summary>
    bool CreateIndexBuffer();

    /// <summary>
    /// 定数バッファを作成
    /// </summary>
    bool CreateConstantBuffer();

    /// <summary>
    /// サンプラーステートを作成
    /// </summary>
    bool CreateSamplerState();

    /// <summary>
    /// ブレンドステートを作成
    /// </summary>
    bool CreateBlendState();

    /// <summary>
    /// テキストフォーマットを作成
    /// </summary>
    bool CreateTextFormat();

    /// <summary>
    /// マトリックスを初期化
    /// </summary>
    void InitMatrix();

public:
    /// <summary>
    /// 描画開始処理
    /// </summary>
    void BeginRendering();

    /// <summary>
    /// 描画終了処理
    /// </summary>
    void EndRendering();

    /// <summary>
    /// 画像読み込み
    /// </summary>
    /// <param name="name">名前</param>
    /// <param name="filePath">ファイルパス</param>
    void LoadTexture(std::string name, std::wstring filePath);

    /// <summary>
    /// 画像描画
    /// </summary>
    /// <param name="name">名前</param>
    /// <param name="x">X座標</param>
    /// <param name="y">Y座標</param>
    void DrawTexture(std::string name, float x, float y);

    /// <summary>
    /// テキスト描画
    /// </summary>
    /// <param name="text">文字</param>
    /// <param name="x">X座標</param>
    /// <param name="y">Y座標</param>
    /// <param name="color">色</param>
    void DrawString(std::wstring text, float x, float y, D2D1::ColorF color);

private:
    struct Vertex
    {
        XMFLOAT4 pos;
        XMFLOAT4 color;
        XMFLOAT2 uv;
    };

private:
    ID3D11Device* m_pDevice;
    ID3D11DeviceContext* m_pContext;
    IDXGISwapChain* m_pSwapChain;
    ID3D11RenderTargetView* m_pRenderTargetView;
    ID3D11VertexShader* m_pVertexShader;
    ID3D11PixelShader* m_pPixelShader;
    ID3D11InputLayout* m_pInputLayout;
    ID3D11Buffer* m_pVertexBuffer;
    ID3D11Buffer* m_pIndexBuffer;
    ID3D11Buffer* m_pConstantBuffer;
    ID3D11SamplerState* m_pSamplerState;
    std::map<std::string, ID3D11ShaderResourceView*> m_pShaderResourceViews;
    std::unordered_map<std::string, std::wstring> m_textureNames;
    ID2D1Factory* m_pD2DFactory;
    IDWriteFactory* m_pDWriteFactory;
    IDWriteTextFormat* m_pTextFormat;
    ID2D1RenderTarget* m_pD2DRenderTarget;
    ID2D1SolidColorBrush* m_pBrush;
};

#endif
