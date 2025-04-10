#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Init(HWND hWnd)
{
}

void Renderer::Update()
{
}

void Renderer::Release()
{
    if (m_Device) {
        m_Device->Release();
        m_Device = nullptr;
    }
    if (m_SwapChain) {
        m_SwapChain->Release();
        m_SwapChain = nullptr;
    }
}
